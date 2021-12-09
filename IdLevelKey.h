
#ifndef OCTOPUS_GAMES_IDLEVELKEY_H
#define OCTOPUS_GAMES_IDLEVELKEY_H

#define DEFAULT_PLAYER_ID -1
#define DEFAULT_PLAYER_LEVEL -1

namespace WET1{
    class IdLevelKey{
        int id;
        int level;

    public:
        IdLevelKey(): id(DEFAULT_PLAYER_ID), level(DEFAULT_PLAYER_LEVEL)
        {}
        IdLevelKey(int id, int level) : id(id), level(level)
        {}

        ~IdLevelKey() = default;

        IdLevelKey& operator=(const IdLevelKey& other)= default;

        bool operator==(const IdLevelKey& other) const{
            return this->id == other.id;
        }

        bool operator<(const IdLevelKey& other) const{
            return this->level < other.level || (this->level == other.level && this->id > other.id);
        }

        bool operator>(const IdLevelKey& other) const{
            return this->level > other.level || (this->level == other.level && this->id < other.id);
        }
    };
}

#endif //OCTOPUS_GAMES_IDLEVELKEY_H
