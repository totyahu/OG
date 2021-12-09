
#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "IdLevelKey.h"

using namespace std;

namespace WET1{
    class Group;

    class Player{
        int id;
        int level;
        shared_ptr<Group> group;
        IdLevelKey key;

        void updateKey();

    public:
        Player()=default;
        Player(int id, int level, shared_ptr<Group> group);
        Player(const Player& other)=default;
        ~Player() = default;//destructor
        bool operator==(const Player& other_player)const;
        bool operator<(const Player& other_player)const;
        bool operator>(const Player& other_player)const;
        IdLevelKey& toKey();
        Player& operator=(const Player& player);
        void increaseLevel(int LevelIncrease);
        int getId();
        shared_ptr<Group>& getGroup();
        int getLevel();
        void changeGroup(shared_ptr<Group> new_group);
    };
}

#endif //PLAYER_H
