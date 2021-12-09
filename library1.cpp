#include "library1.h"
#include "GameManager.h"

using namespace WET1;

void* Init() {
    GameManager *DS = new GameManager();
    return (void*) DS;
}

StatusType AddGroup(void *DS, int GroupID){
    return ((GameManager*) DS)->AddGroup(GroupID);
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level){
    return ((GameManager*) DS)->AddPlayer(PlayerID, GroupID, Level);
}

StatusType RemovePlayer(void *DS, int PlayerID){
    return ((GameManager*) DS)->RemovePlayer(PlayerID);
}

StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID){
    return ((GameManager*) DS)->ReplaceGroup(GroupID, ReplacementID);
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease){
    return ((GameManager*) DS)->IncreaseLevel(PlayerID, LevelIncrease);
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID){
    return ((GameManager*) DS)->GetHighestLevel(GroupID, PlayerID);
}

StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers){
    return ((GameManager*) DS)->GetAllPlayersByLevel(GroupID, Players, numOfPlayers);
}

StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players){
    return ((GameManager*) DS)->GetGroupsHighestLevel(numOfGroups, Players);
}

void Quit(void** DS){
    return GameManager::Quit((GameManager*) DS);
}
