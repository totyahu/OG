
#ifndef OCTOPUS_GAMES_GAMEMANAGER_H
#define OCTOPUS_GAMES_GAMEMANAGER_H

#include "library1.h"
#include "IdLevelKey.h"
#include "Group.h"
#include "Player.h"
#include "Utils.h"


namespace WET1{
    class GameManager {
        unique_ptr<AVLTree<int, shared_ptr<Group>>> groups;
        unique_ptr<AVLTree<int, shared_ptr<Player>>> players_by_id;
        unique_ptr<AVLTree<IdLevelKey, shared_ptr<Player>>> players_by_level;
        unique_ptr<AVLTree<int, shared_ptr<Group>>> not_empty_groups;

//        AVLTree<int, shared_ptr<Group>> * groups;
//        AVLTree<int, shared_ptr<Player>> * players_by_id;
//        AVLTree<IdLevelKey, shared_ptr<Player>> * players_by_level;
//        AVLTree<int, shared_ptr<Group>> * not_empty_groups;

        shared_ptr<Group> findGroup(int group_id);
        shared_ptr<Player> findPlayerById(int player_id);
        shared_ptr<Player> findPlayerByKey(const IdLevelKey& key);


    public:
        explicit GameManager();
//        ~GameManager() = default;
        ~GameManager();
        GameManager *Init();
        StatusType AddGroup(int GroupID);
        StatusType AddPlayer( int PlayerID, int GroupID, int Level);
        StatusType RemovePlayer(int PlayerID);
        StatusType ReplaceGroup(int GroupID, int ReplacementID);
        StatusType IncreaseLevel(int PlayerID, int LevelIncrease);
        StatusType GetHighestLevel( int GroupID, int *PlayerID);
        StatusType GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers);
        StatusType GetGroupsHighestLevel(int numOfGroups, int **Players);
        static void Quit(GameManager* gameManager);

        void printGame();

    };
}


#endif //OCTOPUS_GAMES_GAMEMANAGER_H
