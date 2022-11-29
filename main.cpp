#include <iostream>
#include <random>
#include <time.h>
#include <curses.h>

#include "card.h"
#include "renderer.h"
#include "inputHandler.h"
#include "playerData.h"
#include "gameActions.h"

using namespace std;

playerDataStruct playerObject[4];   //Player object that stores all player values
cardStruct::singleCard cardsTable[5];   //5 table cards

inputHandlerStruct inputHandelerObj;
cardStruct cardObj;
rendererStruct rednererObj;
gameActionsStruct actionsObj;

int gameState = 0;  //State of the game ID (refers to no of cards on the table)
int currPlayer = 0;

int bufferIndex = 0;    //Buffer index
bool initDefNames = true;   //Bool for creating default names for players

void generatePlayerCards()
{
    for (int i = 0; i < 4; i++) //Generate cards for players
    {
        playerObject[i].playerHand[0].rank = (cardStruct::Rank)((rand() % 12) + 1); //Adds +1 for index 2-13
        playerObject[i].playerHand[0].suit = (cardStruct::Suit)((rand() % 4) + 3);
        playerObject[i].playerHand[1].rank = (cardStruct::Rank)((rand() % 12) + 1);
        playerObject[i].playerHand[1].suit = (cardStruct::Suit)((rand() % 4) + 3);
    }
}

void generateTableCards()
{
    for (int i = 0; i < 5; i++)  //Generate cards at the table
    {
        cardsTable[i].rank = (cardStruct::Rank)((rand() % 12) + 1);
        cardsTable[i].suit = (cardStruct::Suit)((rand() % 4) + 3);
    }
}

void bufferAll()
{
    for (int i = 0; i < 5; i++) //Buffer all table cards
    {
        rednererObj.bufferCard(cardsTable[i].rank, cardsTable[i].suit, bufferIndex);
        bufferIndex++;  //Table cards indexes 0-4
    }
    for (int i = 0; i < 4; i++) //Buffer all player cards
    {
        rednererObj.bufferCard(playerObject[i].playerHand[0].rank, playerObject[i].playerHand[0].suit, bufferIndex);
        rednererObj.bufferCard(playerObject[i].playerHand[1].rank, playerObject[i].playerHand[1].suit, bufferIndex + 1);
        bufferIndex += 2;   //Player cards indexes 5-12
    }
    bufferIndex = 0;
}

void createNewGame()
{
    generatePlayerCards();
    generateTableCards();
    bufferAll();
    gameState = 0;  //0 cards at the table shown
}

void switchPlayer()
{
    playerObject[currPlayer].isCurrentPlayer = false;    //Set false flag on current player
    if (currPlayer == 3) //Cycle player
    {
        currPlayer = -1;
    }
    currPlayer++;   //Go to next player index
    playerObject[currPlayer].isCurrentPlayer = true;    //Set true flag on next player
    rednererObj.renderPlayerChangeScreen(currPlayer);
}

void _do_nothing(){}    //Do nothing void

int main()
{
    //=====================================================GAME INIT====================================================
    srand(time(0)); //Set seed of randomizer for current time
    generatePlayerCards();    //Generate cards for players
    generateTableCards();   //Generate cards at the table
    bufferAll();    //Buffer all cards (player and table)

    if (initDefNames)   //Set default player names "Player (no)"
    {
        for (int i = 0; i < 4; i++)
        {
            playerObject[i].playerName = "Player " + to_string(i + 1);
        }
    }
    playerObject[0].isCurrentPlayer = true; //Player 1 is current player
    currPlayer = 0; //Player 1 is current player new tracker
    
    //===================================================RENDER LOOP==================================================
    while (true)    //Gameplay loop
    {
        rednererObj.renderScreen(inputHandelerObj.cursorPos, playerObject, currPlayer, gameState, actionsObj); //Render screen from buffer
        switch (inputHandelerObj.getInput())
        {
        case 2: //M button pressed
            gameState++;
            break;

        case 3: //N button pressed
            //gameState++;    //Go to the next game stage
            switchPlayer();
            break;
        
        case 4: //Fold button pressed
            actionsObj.foldAction();
            break;

        case 5: //Call button pressed
            actionsObj.callAction();
            break;

        case 6: //Raise button pressed
            if (actionsObj.raiseAction(playerObject[currPlayer]))   //If returns without an error
            {
                playerObject[currPlayer] = actionsObj.fetchPlayerData();    //Update player data
                cin.get();
                cin.get();
                switchPlayer();
            }
            break;
        
        default:
            break;
        }
    }
    return 0;
}
