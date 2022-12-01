#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <string>

#include "card.h"

struct playerDataStruct
{
    int money = 10000;
    int moneyPut;   //Money put to table at current round
    std::string playerName;  //Name of a player
    cardStruct::singleCard playerHand[2];   //2 cards in players hand
    bool isCurrentPlayer = false;
    std::string lastPlayerAction = "";
    bool folded;
    bool inGame;
};

#endif