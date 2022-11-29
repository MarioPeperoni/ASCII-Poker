#ifndef GAMEACTIONS_H
#define GAMEACTIONS_H

#include <string>

#include "playerData.h"

struct gameActionsStruct
{
    std::string currentActionText;  //UI custom text
    std::string bufferedRaiseVisBar;    //Visual representation of bar for raise action

    bool foldAction(playerDataStruct playerObj);
    bool callAction(playerDataStruct playerObj);
    bool raiseAction(playerDataStruct playerObj);
    playerDataStruct fetchPlayerData();
};


#endif