#ifndef GAMEACTIONS_H
#define GAMEACTIONS_H

#include <string>

#include "playerData.h"
#include "card.h"

struct gameActionsStruct
{
    std::string currentActionText;  //UI custom text
    std::string bigActionText;  //UI big action text on the middle
    std::string bufferedRaiseVisBar;    //Visual representation of bar for raise action

    int gameState;  //State of the game ID (refers to no of cards on the table)
    int turnsPlayed = 0;    //Number of turns played
    int currentPot; //Value of current pot
    
    int highestCall;    //Highest call in the game

    int currentHiBlind;   //Current hi blind values
    int checkBlinds(int turnsPlayed);
    void takeBlinds(playerDataStruct smallBlindPlayer, playerDataStruct bigBlindPlayer);    //Take blind money from players
    int currentBigBlindPlayer;
    int currentSmallBlindPlayer;

    //======================================PLAYER ACTIONS==========================================
    bool checkAction(playerDataStruct playerObj);   //Call check action
    bool foldAction(playerDataStruct playerObj);    //Call fold cation on player
    bool callAction(playerDataStruct playerObj);    //Calls call action on player
    bool raiseAction(playerDataStruct playerObj);   //Calls raise action on player
    bool bidAction(playerDataStruct playerObj);     //Calls bid action on player

    void increaseGameState();
    void determineRoundWinner(playerDataStruct playersObj[4]);
    void calculateScore(playerDataStruct player, int gameState, cardStruct::singleCard cardsTable[5]);
    void determineNextRoundStartingPlayer(playerDataStruct playerObj[4]);   //Void for changing first player increasting round
    void lookForSets(playerDataStruct playerObj, int gameState, cardStruct::singleCard tableCards[5]);

    playerDataStruct fetchPlayerData();
    playerDataStruct fetchPlayerData(int indexInMem);
};


#endif