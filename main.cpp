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
cardStruct::singleCard cardsGame[13];   //Storing all cards in game (only used for comp)

inputHandlerStruct inputHandelerObj;
cardStruct cardObj;
rendererStruct rednererObj;
gameActionsStruct actionsObj;

int gameState = 0;  //State of the game ID (refers to no of cards on the table)
int currPlayer = 0;

int cardsGenerated = 0; //Index for generated cards (used for comp)
int bufferIndex = 0;    //Buffer index
bool initDefNames = true;   //Bool for creating default names for players

bool checkIfCardValid(bool isTable, int playerID, int cardID)
{
    for (int i = 0; i < cardsGenerated + 1; i++)
    {
        if (isTable)
        {
            if (cardsTable[cardID].rank == cardsGame[i].rank && cardsTable[cardID].suit == cardsGame[i].suit)
            {
                return false;
            }
        }
        else
        {
            if (playerObject[playerID].playerHand[cardID].rank == cardsGame[i].rank && playerObject[playerID].playerHand[cardID].suit == cardsGame[i].suit)
            {
                return false;
            }
        }
    }
    return true;
}

void generatePlayerCards(int playerID)
{
    //Generate 1st card for player
    generate1stCardLabel:
    playerObject[playerID].playerHand[0].rank = (cardStruct::Rank)((rand() % 12) + 1);
    playerObject[playerID].playerHand[0].suit = (cardStruct::Suit)((rand() % 4) + 3);
    if (!checkIfCardValid(false, playerID, 0))  //If card is valid
    {
       goto generate1stCardLabel;   ////Try generating agiain
    }
    cardsGame[cardsGenerated].rank = playerObject[playerID].playerHand[0].rank; //Add valid generated card to game deck
    cardsGame[cardsGenerated].suit = playerObject[playerID].playerHand[0].suit;
    cardsGenerated++;   //Move index of cardsGame

    //Generate 2nd card for player
    generate2ndCardLabel:
    playerObject[playerID].playerHand[1].rank = (cardStruct::Rank)((rand() % 12) + 1);
    playerObject[playerID].playerHand[1].suit = (cardStruct::Suit)((rand() % 4) + 3);
    if (!checkIfCardValid(false, playerID, 1))  //If card is valid
    {
       goto generate2ndCardLabel;   //Try generating agiain
    }
    cardsGame[cardsGenerated].rank = playerObject[playerID].playerHand[1].rank; //Add valid generated card to game deck
    cardsGame[cardsGenerated].suit = playerObject[playerID].playerHand[1].suit;
    cardsGenerated++;   //Move index of cardsGame
}

void generateTableCards()
{
    for (int i = 0; i < 5; i++)  //Generate cards at the table
    {
        generateTableCardAgainLabel:
        cardsTable[i].rank = (cardStruct::Rank)((rand() % 12) + 1);
        cardsTable[i].suit = (cardStruct::Suit)((rand() % 4) + 3);
        if (!checkIfCardValid(true, 0, i))  //If card is valid
        {
            goto generateTableCardAgainLabel;   //Try again
        }
        cardsGame[cardsGenerated].rank = cardsTable[i].rank;    //Add valid generated card to game deck
        cardsGame[cardsGenerated].suit = cardsTable[i].suit;
        cardsGenerated++;   //Move index of cardsGame
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
    cardsGenerated = 0; //Prepare to generate new set of cards
    generateTableCards();   //Generate cards at the table
    for (int i = 0; i < 4; i++)
    {
        generatePlayerCards(i); //Generate cards for eatch player
    }
    bufferAll();    //Buffer all cards (player and table)
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
    playerObject[currPlayer].folded ? switchPlayer() : rednererObj.renderPlayerChangeScreen(currPlayer);    //Check if player fold
}

void _do_nothing(){}    //Do nothing void

int main()
{
    //=====================================================GAME INIT====================================================
    srand(time(0)); //Set seed of randomizer for current time
    createNewGame();

    if (initDefNames)   //Set default player names "Player (no)"
    {
        for (int i = 0; i < 4; i++)
        {
            playerObject[i].playerName = "Player " + to_string(i + 1);
        }
    }
    playerObject[0].isCurrentPlayer = true; //Player 1 is current player
    currPlayer = 0; //Player 1 is current player (new tracker)
    
    //===================================================RENDER LOOP==================================================
    while (true)    //Gameplay loop
    {
        rednererObj.renderScreen(inputHandelerObj.cursorPos, playerObject, currPlayer, gameState, actionsObj); //Render screen from buffer
        switch (inputHandelerObj.getInput())
        {
        case 2: //M button pressed
            gameState++;    //Go to the next game stage
            break;

        case 3: //N button pressed
            switchPlayer();
            break;
        
        case 4: //Fold button pressed
            actionsObj.foldAction(playerObject[currPlayer]);
            playerObject[currPlayer] = actionsObj.fetchPlayerData();
            cin.get();
            cin.get();
            switchPlayer();
            break;

        case 5: //Call button pressed
            actionsObj.callAction(playerObject[currPlayer]);
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
