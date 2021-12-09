
#include "Player.h"
#include "Group.h"


//using namespace WET1;

namespace WET1{
    Player::Player(int id, int level, shared_ptr<Group> group):
            id(id), level(level)
    {
        this->group = group;
        this->key = IdLevelKey(id, level);
    }

//    Player::~Player() {
//        this->group->reset();
//    }

    bool Player::operator==(const Player &other_player)const {
        return (this->id == other_player.id);
    }

    bool Player::operator<(const Player & other_player) const{
        return this->id < other_player.id;
    }

    bool Player::operator>(const Player & other_player) const{
        return this->id > other_player.id;
    }

    Player& Player::operator=(const Player& player){
        this->id = player.id;
        this->level = player.level;
        this->group = player.group;
        return *this;
    }

    void Player::increaseLevel(int LevelIncrease){
        this->level += LevelIncrease;
        this->updateKey();
    }

    int Player::getId() {
        return this->id;
    }

    shared_ptr<Group>& Player::getGroup(){
        return this->group;
    }

    int Player::getLevel() {
        return this->level;
    }

    void Player::changeGroup(shared_ptr<Group> new_group) {
        this->group = new_group;
    }

    IdLevelKey& Player::toKey() {
        return this->key;
    }

    void Player::updateKey(){
        this->key = IdLevelKey(id, level);
    }

}

