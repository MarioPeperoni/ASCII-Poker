#include <iostream>

#include "gameActions.h"
#include "renderer.h"
#include "playerData.h"

rendererStruct rendererObj;
playerDataStruct fetchedPlayerObj;

bool gameActionsStruct::foldAction()
{
    return false;
}

bool gameActionsStruct::callAction()
{
    return false;
}

bool gameActionsStruct::raiseAction(playerDataStruct playerObj)
{
    int raisedMoney;    //Money inputed from player
    rendererObj.SetCursorPos(UI_CALL_INPUT_BOX_POS, UI_BUTTON_ROW_ID);  //Cursor positon set to call input box
    gameActionsStruct::currentActionText = "Insert raise value...";
    std::cin >> raisedMoney;
    if (raisedMoney > playerObj.money)  //If player do not have enough money in balance
    {
        rendererObj.SetCursorPos(UI_CALL_INPUT_BOX_POS, UI_BUTTON_ROW_ID);  //Cursor positon set to call input box
        gameActionsStruct::currentActionText = "Raise too big. Try again...";
        return false;   //Action not finished
    }
    gameActionsStruct::currentActionText = "Raised " + std::to_string(raisedMoney) + "$";
    playerObj.money -= raisedMoney; //Subtract raised moeny from player balance
    playerObj.lastPlayerAction = "Raised " + std::to_string(raisedMoney) + "$";
    fetchedPlayerObj = playerObj;   //Copy contents of playerObj to fetchedPlayerObj
    return true;    //Action finished succesfully
}

playerDataStruct gameActionsStruct::fetchPlayerData()
{
    return fetchedPlayerObj;
}