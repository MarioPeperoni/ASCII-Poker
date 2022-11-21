#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <string>

#include "card.h"

struct playerDataStruct
{
    int money = 10000;
    std::string playerName;  //Name of a player
    cardStruct::singleCard playerHand[2];   //2 cards in players hand
    bool isCurrentPlayer = false;
};

#endif