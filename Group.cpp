
#include "Group.h"
#include "Player.h"

using namespace std;

#define DEFAULT_ID -1


namespace WET1{
    Group::Group() : id(DEFAULT_ID){
        this->players = nullptr;
    }

    Group::Group(int id) : id(id){
        this->players = std::unique_ptr<AVLTree<IdLevelKey, shared_ptr<Player>>>(new AVLTree<IdLevelKey, shared_ptr<Player>>());
    }

    Group::~Group(){
        this->players.reset();
//        delete this->players;
//        this->players = nullptr;
    }

    bool Group::operator==(const Group& other_group){
        return this->id == other_group.id;
    }

    bool Group::operator<(const Group& other_group){
        return this->id < other_group.id;
    }

    bool Group::playerExist(int id, int level){
        return this->players->exists(IdLevelKey(id, level));
    }

    void Group::addPlayer(shared_ptr<Player> player){
        this->players->insert(player->toKey(), player);
    }

    void Group::removePlayer(shared_ptr<Player> player){
        this->players->remove(player->toKey());
    }


    int Group::getHighestLevel(){
        if(this->players == nullptr || this->players->getMax() == nullptr){
            return DEFAULT_ID;
        }
        return (*(this->players->getMax()))->getId();
    }

    bool Group::isEmpty() const{
        return !this->players || (this->players && !this->players->getSize());
    }

    void updateGroup(shared_ptr<Player> player, void* new_group){
        shared_ptr<Group> ptr((Group*)new_group);
        if(!(player->getGroup() == ptr)){
            player->changeGroup(ptr);
        }
    }


    bool Group::mergeGroup(shared_ptr<Group> other_group){
        if(this->isEmpty()){
            this->players.swap(other_group->players);
//            other_group->players.reset();
//            delete other_group->players;
//            other_group->players = nullptr;

            this->players->apply(updateGroup, this);
            return true;
        }

        unique_ptr<AVLTree<IdLevelKey, shared_ptr<Player>>> merged_tree = AVLTree<IdLevelKey, shared_ptr<Player>>::merge(
                *(this->players), *(other_group->players)
        );

        if(merged_tree == nullptr){
            return false;
        }

        this->players.reset();
        this->players.swap(merged_tree);
        merged_tree.reset();
        this->players->apply(updateGroup, this);

        return true;
    }

    int Group::getId() {
        return this->id;
    }

    int Group::getSize(){
        return this->players->getSize();
    }

    int Group::getBestPlayerId(){
        return this->players == nullptr ? DEFAULT_ID : (*this->players->getMax())->getId();
    }

    void Group::toSortedArray(IdLevelKey dest_arr_keys[], shared_ptr<Player> dest_arr_players[]){
        this->players->toSortedArray(dest_arr_keys, dest_arr_players);
    }

}