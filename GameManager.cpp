
#include "GameManager.h"

using namespace WET1;

//namespace WET1{
    GameManager::GameManager(){
        this->players_by_id = new AVLTree<int, shared_ptr<Player>>();
        this->players_by_level = new AVLTree<IdLevelKey, shared_ptr<Player>>();
        this->groups = new AVLTree<int, shared_ptr<Group>>();
        this->not_empty_groups= new AVLTree<int, shared_ptr<Group>>();
    }

    GameManager * GameManager::Init() {
        return new GameManager();
    }

    StatusType GameManager::AddGroup(int GroupID){
        if(GroupID <= 0){
            return  INVALID_INPUT;
        }

        if(this->groups->exists(GroupID)){
            return FAILURE;
        }

        this->groups->insert(GroupID, make_shared<Group>(GroupID));

        return SUCCESS;
    }

    StatusType GameManager::AddPlayer(int PlayerID, int GroupID, int Level){
        if(PlayerID <= 0 || GroupID <= 0 || Level < 0){
            return INVALID_INPUT;
        }

        shared_ptr<Group> group = *(this->groups->find(GroupID));
        if(this->players_by_id->exists(PlayerID) || group == nullptr){
            return FAILURE;
        }

        shared_ptr<Player> player = make_shared<Player>(PlayerID, Level, group);
        this->players_by_id->insert(PlayerID, player);
        this->players_by_level->insert(player->toKey(), player);

        if(group->isEmpty()){
            this->not_empty_groups->insert(group->getId(), group);
        }

        group->addPlayer(player);

        return SUCCESS;
    }

    StatusType GameManager::RemovePlayer(int PlayerID){
        if(PlayerID <= 0){
            return INVALID_INPUT;
        }

        shared_ptr<Player> player(*(this->players_by_id->find(PlayerID)));

        if(player == nullptr){
            return FAILURE;
        }

        this->players_by_id->remove(PlayerID);
        this->players_by_level->remove(player->toKey());


        shared_ptr<Group> group(player->getGroup());
        group->removePlayer(player);


        if(group->isEmpty()){
            this->not_empty_groups->remove(group->getId());
        }

        return SUCCESS;
    }

    StatusType GameManager::IncreaseLevel(int PlayerID, int LevelIncrease){//TODO: make sure everyone point to same player
        if(PlayerID <= 0 || LevelIncrease <= 0){
            return INVALID_INPUT;
        }

        shared_ptr<Player> player_by_id(*(this->players_by_id->find(PlayerID)));

        if(player_by_id == nullptr){
            return FAILURE;
        }

        shared_ptr<Player> player_by_level(*(this->players_by_level->find(player_by_id->toKey())));

        shared_ptr<Group> group = player_by_id->getGroup();

        this->players_by_id->remove(PlayerID);
        this->players_by_level->remove(player_by_level->toKey());
        group->removePlayer(player_by_level);

        player_by_level->increaseLevel(LevelIncrease);

        this->players_by_id->insert(PlayerID, player_by_id);
        this->players_by_level->insert(player_by_level->toKey(), player_by_level);
        group->addPlayer(player_by_level);

        return SUCCESS;
    }

    StatusType GameManager::GetHighestLevel(int GroupID, int *PlayerID) {
        if(PlayerID == nullptr || GroupID == 0){
            return INVALID_INPUT;
        }

        if(GroupID < 0){
            shared_ptr<Player>* M_ptr = this->players_by_level->getMax();
            if(M_ptr == nullptr){
                *PlayerID = -1;
            }
            else{
                *PlayerID = (*M_ptr)->getId();
            }
            return SUCCESS;
        }

        else{
            shared_ptr<Group> group = *(this->groups->find(GroupID));

            if(group == nullptr){
                return FAILURE;
            }

            if(group->isEmpty()){
                *PlayerID = -1;
                return SUCCESS;
            }

            *PlayerID = group->getHighestLevel();
            return SUCCESS;
        }

    }

    StatusType GameManager::ReplaceGroup(int GroupID, int ReplacementID){
        if(GroupID <= 0 || ReplacementID <= 0 || GroupID == ReplacementID){
            return INVALID_INPUT;
        }

        shared_ptr<Group> delete_group = *(this->groups->find(GroupID));
        shared_ptr<Group> replace_group = *(this->groups->find(ReplacementID));

        if(delete_group == nullptr || replace_group == nullptr){
            return FAILURE;
        }

        if(!delete_group->isEmpty()){
            if(replace_group->isEmpty()){
                this->not_empty_groups->insert(ReplacementID, replace_group);
            }
            this->not_empty_groups->remove(GroupID);


            if(!replace_group->mergeGroup(delete_group)){
                return ALLOCATION_ERROR;
            }
        }

        this->groups->remove(GroupID);
        return SUCCESS;
    }

    StatusType GameManager::GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers){
        if(GroupID == 0 || Players == nullptr || numOfPlayers == nullptr){
            return INVALID_INPUT;
        }

        if(GroupID < 0){
            *numOfPlayers = this->players_by_level->getSize();
            if(*numOfPlayers == 0){
                *Players = NULL;
                return SUCCESS;
            }

            auto tmp_keys = new IdLevelKey[*numOfPlayers];
            auto tmp_players = new shared_ptr<Player>[*numOfPlayers];

            this->players_by_level->toSortedArray(tmp_keys, tmp_players);


            *Players = (int*)malloc(sizeof(int) * (*numOfPlayers));
            if(*Players == NULL){
                cout << "fuck"  << endl;
                return ALLOCATION_ERROR;
            }

            for(int i = 0; i < *numOfPlayers; i++){
                (*Players)[i] = tmp_players[*numOfPlayers - i - 1]->getId();
//                delete &(tmp[*numOfPlayers - i - 1]);
            }

            delete[] tmp_keys;
            delete[] tmp_players;
            return SUCCESS;
        }
        else {
            shared_ptr<Group> group = *(this->groups->find(GroupID));
            if(group == nullptr){
                return FAILURE;
            }

            *numOfPlayers = group->getSize();
            if(*numOfPlayers == 0){
                *Players = NULL;
                return SUCCESS;
            }

            *Players = (int*)malloc(sizeof(int) * (*numOfPlayers));
            if(*Players == NULL){
                cout << "fuck"  << endl;
                return ALLOCATION_ERROR;
            }
//        *Players = new int[*numOfPlayers];


            auto tmp_keys = new IdLevelKey[*numOfPlayers];
            auto tmp_players = new shared_ptr<Player>[*numOfPlayers];

            group->toSortedArray(tmp_keys, tmp_players);

            for(int i = 0; i < *numOfPlayers; i++){
                (*Players)[i] = tmp_players[*numOfPlayers - i - 1]->getId();
//                delete &(tmp[*numOfPlayers - i - 1]);
            }

            delete[] tmp_keys;
            delete[] tmp_players;
            return SUCCESS;
        }

    }


    bool groupNotEmpty(const Group& group){
        return !group.isEmpty();
    }

    StatusType GameManager::GetGroupsHighestLevel(int numOfGroups, int **Players){
        if(Players == nullptr || numOfGroups < 1){
            return INVALID_INPUT;
        }

        if(this->not_empty_groups->getSize() < numOfGroups){
            return FAILURE;
        }

        *Players = (int*)malloc(sizeof(int) * (numOfGroups));
        if(*Players == NULL){
            return ALLOCATION_ERROR;
        }

        auto tmp_ids = new int[numOfGroups];
        auto tmp_groups = new shared_ptr<Group>[numOfGroups];
        this->not_empty_groups->toSortedArray(tmp_ids, tmp_groups);


        for(int i = 0; i < numOfGroups; i++){
            (*Players)[i] = tmp_groups[i]->getBestPlayerId();
//            delete &(tmp[numOfGroups - i - 1]);
        }

       delete[] tmp_ids;
       delete[] tmp_groups;
        return SUCCESS;
    }


    void GameManager::Quit(GameManager* gameManager){
        delete gameManager;
    }


    GameManager::~GameManager() {
        delete players_by_level;
        delete players_by_id;
        delete groups;
        delete not_empty_groups;
    }

//}