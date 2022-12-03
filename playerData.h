#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <string>

#include "card.h"

struct playerDataStruct
{
    int money = 10000;                    // Money tracker: starting money 10000
    int moneyPut;                         // Money put to table at current round
    std::string playerName;               // Name of a player
    cardStruct::singleCard playerHand[2]; // 2 cards in players hand
    bool isCurrentPlayer = false;
    std::string lastPlayerAction = ""; // String for drawing under the player name
    bool folded;
    bool inGame;
    bool nextRoundPlayer; // If round progresses from this player

    std::string setName; // Name of card set
    int valueOfSet;      // Returns value of type of set
    cardStruct::singleCard hiCardInSet;     // ID of highest card in set
};

#endif