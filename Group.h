#ifndef OCTOPUS_GAMES_GROUP_H
#define OCTOPUS_GAMES_GROUP_H

#include <memory>
#include "AVLTree.h"
#include "IdLevelKey.h"


namespace WET1{
    class Player;

    class Group {
        int id;
        unique_ptr<AVLTree<IdLevelKey, shared_ptr<Player>>> players;

    public:
        Group();
        explicit Group(int group_id);
        ~Group();
        bool operator==(const Group& other_group);
        bool operator<(const Group& other_group);
        bool playerExist(int id, int level);
        void addPlayer(shared_ptr<Player> player);
        void removePlayer(shared_ptr<Player> player);
        void increaseLevel(Player& player, int increase_level);
        int getHighestLevel();
        bool isEmpty() const;
        int getId();
        int getSize();
        int getBestPlayerId();
        bool mergeGroup(shared_ptr<Group> other_group);
        void printPlayers();
        void resGroup();

        void toSortedArray(IdLevelKey dest_arr_keys[], shared_ptr<Player> dest_arr_players[]);

    };
}

#endif //OCTOPUS_GAMES_GROUP_H
