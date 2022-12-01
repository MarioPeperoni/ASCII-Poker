#include <iostream>

#include "gameActions.h"
#include "renderer.h"
#include "playerData.h"

rendererStruct rendererObj;
playerDataStruct fetchedPlayerObj[2];

bool gameActionsStruct::foldAction(playerDataStruct playerObj)
{
    playerObj.folded = true;    //Flag fold
    playerObj.lastPlayerAction = "Folded";  //Set player last action string
    gameActionsStruct::currentActionText = "Folded";    //Set action text
    fetchedPlayerObj[0] = playerObj;   //Copy contents of playerObj to fetchedPlayerObj
    return true;
}

bool gameActionsStruct::checkAction(playerDataStruct playerObj)
{
    playerObj.lastPlayerAction = "Checked";  //Set player last action string
    fetchedPlayerObj[0] = playerObj; //Copy contents of playerObj to fetchedPlayerObj
    return true;
}

bool gameActionsStruct::callAction(playerDataStruct playerObj)
{
    playerObj.money -= gameActionsStruct::highestCall - playerObj.moneyPut;
    playerObj.moneyPut += gameActionsStruct::highestCall - playerObj.moneyPut;
    gameActionsStruct::currentPot += gameActionsStruct::highestCall;    //Increase current pot call value
    gameActionsStruct::currentActionText = "Called";    //Set action text
    playerObj.lastPlayerAction = "Called"; //Set player last action string
    fetchedPlayerObj[0] = playerObj;
    return false;
}

bool gameActionsStruct::raiseAction(playerDataStruct playerObj)
{
    int raisedMoney;    //Money inputed from player
    rendererObj.SetCursorPos(UI_CALL_INPUT_BOX_POS_X, UI_CALL_INPUT_BOX_POS_Y);  //Cursor positon set to call input box
    gameActionsStruct::currentActionText = "Insert raise value...";
    std::cin >> raisedMoney;
    if ((raisedMoney + highestCall) > playerObj.money)  //If player do not have enough money in balance
    {
        gameActionsStruct::currentActionText = "Raise too big. Try again...";
        return false;   //Action not finished
    }
    highestCall += raisedMoney; //Add raise value to highest call
    playerObj.moneyPut += highestCall;  //Add raise value to money put in pot
    gameActionsStruct::currentActionText = "Raised " + std::to_string(highestCall) + "$";
    playerObj.money -= (highestCall); //Subtract raised moeny from player balance
    gameActionsStruct::currentPot += highestCall;   //Add money to pot
    playerObj.lastPlayerAction = "Raised " + std::to_string(highestCall) + "$"; //Set player last action string
    fetchedPlayerObj[0] = playerObj;   //Copy contents of playerObj to fetchedPlayerObj
    return true;    //Action finished succesfully
}

bool gameActionsStruct::bidAction(playerDataStruct playerObj)
{
    int raisedMoney;    //Money inputed from player
    rendererObj.SetCursorPos(UI_CALL_INPUT_BOX_POS_X, UI_CALL_INPUT_BOX_POS_Y);  //Cursor positon set to call input box
    gameActionsStruct::currentActionText = "Insert bid value...";
    std::cin >> raisedMoney;
    if (raisedMoney > playerObj.money)  //If player do not have enough money in balance
    {
        gameActionsStruct::currentActionText = "Bid too big. Try again...";
        return false;   //Action not finished
    }
    gameActionsStruct::currentActionText = "Bidded " + std::to_string(raisedMoney) + "$";
    playerObj.money -= raisedMoney; //Subtract raised moeny from player balance
    gameActionsStruct::currentPot += raisedMoney;   //Add money to pot
    playerObj.lastPlayerAction = "Bidded " + std::to_string(raisedMoney) + "$"; //Set player last action string
    highestCall += raisedMoney; //Add raise value to highest call
    playerObj.moneyPut += raisedMoney;  //Add raise value to money put in pot
    fetchedPlayerObj[0] = playerObj;   //Copy contents of playerObj to fetchedPlayerObj
    return true;    //Action finished succesfully
}

int gameActionsStruct::checkBlinds(int turnsPlayed) //Set new blinds every 4 turns
{
    switch (turnsPlayed)
    {
    //Blind level 1
    case 0: //Initial blinds
        gameActionsStruct::currentHiBlind = 200;
        gameActionsStruct::bigActionText = "Blinds are now " + std::to_string(gameActionsStruct::currentHiBlind / 2) + "$ - " + std::to_string(gameActionsStruct::currentHiBlind) + "$";    //Set text
        break;

    //Blind level 2
    case 4:     //1st raise
        gameActionsStruct::currentHiBlind = 400;
        gameActionsStruct::bigActionText = "Blinds are now " + std::to_string(gameActionsStruct::currentHiBlind / 2) + "$ - " + std::to_string(gameActionsStruct::currentHiBlind) + "$";    //Set text
        break;

    //Blind level 3
    case 8:     //2nd raise
        gameActionsStruct::currentHiBlind = 600;
        gameActionsStruct::bigActionText = "Blinds are now " + std::to_string(gameActionsStruct::currentHiBlind / 2) + "$ - " + std::to_string(gameActionsStruct::currentHiBlind) + "$";    //Set text
        break;

    //Blind level 4
    case 12:    //3rd raise
        gameActionsStruct::currentHiBlind = 1000;
        gameActionsStruct::bigActionText = "Blinds are now " + std::to_string(gameActionsStruct::currentHiBlind / 2) + "$ - " + std::to_string(gameActionsStruct::currentHiBlind) + "$";    //Set text
        break;

    //Blind level 5
    case 14:    //4th raise
        gameActionsStruct::currentHiBlind = 2000;
        gameActionsStruct::bigActionText = "Blinds are now " + std::to_string(gameActionsStruct::currentHiBlind / 2) + "$ - " + std::to_string(gameActionsStruct::currentHiBlind) + "$";    //Set text
        break;

    //Blind level 6
    case 16:    //5th raise
        gameActionsStruct::currentHiBlind = 3000;
        gameActionsStruct::bigActionText = "Blinds are now " + std::to_string(gameActionsStruct::currentHiBlind / 2) + "$ - " + std::to_string(gameActionsStruct::currentHiBlind) + "$";    //Set text
        break;

    //Blind level 7
    case 18:    //6th raise
        gameActionsStruct::currentHiBlind = 4000;
        gameActionsStruct::bigActionText = "Blinds are now " + std::to_string(gameActionsStruct::currentHiBlind / 2) + "$ - " + std::to_string(gameActionsStruct::currentHiBlind) + "$";    //Set text
        break;

    //Blind level 8
    case 20:    //7th raise
        gameActionsStruct::currentHiBlind = 8000;
        gameActionsStruct::bigActionText = "Blinds are now " + std::to_string(gameActionsStruct::currentHiBlind / 2) + "$ - " + std::to_string(gameActionsStruct::currentHiBlind) + "$";    //Set text
        break;

    //Blind level 9
    case 22:    //8th raise
        gameActionsStruct::currentHiBlind = 16000;
        gameActionsStruct::bigActionText = "Blinds are now " + std::to_string(gameActionsStruct::currentHiBlind / 2) + "$ - " + std::to_string(gameActionsStruct::currentHiBlind) + "$";    //Set text
        break;
    
    default:
        gameActionsStruct::bigActionText = "";
        break;
    }

    return gameActionsStruct::currentHiBlind;
}

void gameActionsStruct::takeBlinds(playerDataStruct smallBlindPlayer, playerDataStruct bigBlindPlayer)  //Take money for blinds from players
{
    smallBlindPlayer.money -= (currentHiBlind / 2); //Small blind is hi blind value / 2
    bigBlindPlayer.money -= currentHiBlind;
    gameActionsStruct::currentPot += (currentHiBlind / 2) + currentHiBlind; //Add blinds to pot value
    gameActionsStruct::highestCall = currentHiBlind + (currentHiBlind / 2);    //Set inital call value to hi blind
    smallBlindPlayer.moneyPut = (currentHiBlind / 2);
    bigBlindPlayer.moneyPut = currentHiBlind;
    fetchedPlayerObj[0] = smallBlindPlayer; //Fetch small blind player data
    fetchedPlayerObj[1] = bigBlindPlayer;   //Fetch big blind player data
} 

playerDataStruct gameActionsStruct::fetchPlayerData()   //Send player data to main function
{
    return fetchedPlayerObj[0]; //Return modified player object
}

playerDataStruct gameActionsStruct::fetchPlayerData(int indexInMem)   //Send player data to main function
{
    switch (indexInMem)
    {
    case 0:
        return fetchedPlayerObj[0];
        break;
    
    case 1:
        return fetchedPlayerObj[1];
        break;
    }
    return fetchedPlayerObj[0];
}