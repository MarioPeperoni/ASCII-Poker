#include <iostream>
#include <random>
#include <time.h>
#include <curses.h>
#include <unistd.h>

#include "card.h"
#include "renderer.h"
#include "inputHandler.h"
#include "playerData.h"
#include "gameActions.h"

#define WAIT_TIME_BETWEEN_ACTIONS 1

using namespace std;

playerDataStruct playerObject[4];   //Player object that stores all player values
cardStruct::singleCard cardsTable[5];   //5 table cards
cardStruct::singleCard cardsGame[13];   //Storing all cards in game (only used for comp)

inputHandlerStruct inputHandelerObj;
cardStruct cardObj;
rendererStruct rednererObj;
gameActionsStruct actionsObj;

int currPlayer = 0;         //Current player int

int cardsGenerated = 0;     //Index for generated cards (used for comp)
int bufferIndex = 0;        //Buffer index
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
    actionsObj.gameState = 0;  //0 cards at the table shown
    actionsObj.currentHiBlind = actionsObj.checkBlinds(actionsObj.turnsPlayed); //Set blinds
    actionsObj.currentPot = 0;  //Set current pot for 0$

    //=================================================SET BLINDS=================================================
    //Set index for big blind player
    actionsObj.currentBigBlindPlayer == 3 ? actionsObj.currentBigBlindPlayer = 0 : actionsObj.currentBigBlindPlayer++;   //Go to the next index
    while (!playerObject[actionsObj.currentBigBlindPlayer].inGame == false)  //If player is still playing
    {
        actionsObj.currentBigBlindPlayer == 3 ? actionsObj.currentBigBlindPlayer = 0 : actionsObj.currentBigBlindPlayer++;   //Go to the next index
    }    

    //Set index for small blind player
    actionsObj.currentSmallBlindPlayer == 3 ? actionsObj.currentSmallBlindPlayer = 0 : actionsObj.currentSmallBlindPlayer++;   //Go to the next index
    while (!playerObject[actionsObj.currentSmallBlindPlayer].inGame == false)  //If player is still playing
    {
        actionsObj.currentSmallBlindPlayer == 3 ? actionsObj.currentSmallBlindPlayer = 0 : actionsObj.currentSmallBlindPlayer++;   //Go to the next index
    }
    actionsObj.takeBlinds(playerObject[actionsObj.currentSmallBlindPlayer], playerObject[actionsObj.currentBigBlindPlayer]);    //Take money for blinds from player

    playerObject[actionsObj.currentSmallBlindPlayer] = actionsObj.fetchPlayerData(0);   //Upodate player data
    playerObject[actionsObj.currentBigBlindPlayer] = actionsObj.fetchPlayerData(1); //Update player data
}

void _do_nothing(){}    //Do nothing void

void switchPlayer(bool playerChangeScreen)
{
    playerObject[currPlayer].isCurrentPlayer = false;    //Set false flag on current player
    currPlayer == 3 ? currPlayer = 0 : currPlayer++;    //Loop players
    playerObject[currPlayer].isCurrentPlayer = true;    //Set true flag on next player
    if (playerObject[currPlayer].nextRoundPlayer)   //Check if round looped
    {
        actionsObj.increaseGameState(); //Increase game state
    }
    
    if (playerChangeScreen)
    {
        playerObject[currPlayer].folded ? switchPlayer(true) : rednererObj.renderPlayerChangeScreen(currPlayer);    //Check if player fold
        playerObject[currPlayer].inGame ? switchPlayer(true) : rednererObj.renderPlayerChangeScreen(currPlayer);    //Check if is still in game
    }
    
    playerObject[currPlayer].folded ? switchPlayer(false) : _do_nothing();    //Check if player fold
    playerObject[currPlayer].inGame ? switchPlayer(false) : _do_nothing();    //Check if is still in game
}

int main()
{
    //=====================================================GAME INIT====================================================
    srand(time(0)); //Set seed of randomizer for current time
    actionsObj.currentBigBlindPlayer = rand() % 4;
    actionsObj.currentSmallBlindPlayer = actionsObj.currentBigBlindPlayer - 1;
    playerObject[actionsObj.currentBigBlindPlayer].isCurrentPlayer = true; //Player 1 is current player
    currPlayer = actionsObj.currentBigBlindPlayer ; //Player 1 is current player (new tracker)
    switchPlayer(false);
    switchPlayer(true);
    playerObject[currPlayer].nextRoundPlayer = true;
    createNewGame();

    if (initDefNames)   //Set default player names "Player (no)"
    {
        for (int i = 0; i < 4; i++)
        {
            playerObject[i].playerName = "Player " + to_string(i + 1);
        }
    }
    
    //===================================================RENDER LOOP==================================================
    while (true)    //Gameplay loop
    {
        rednererObj.renderScreen(inputHandelerObj.cursorPos, playerObject, currPlayer, actionsObj); //Render screen from buffer
        switch (inputHandelerObj.getInput())
        {
        case 2: //DEBUG 1: Inc Game state
            actionsObj.gameState++;    //Go to the next game stage
            break;

        case 3: //DEBUG 2: Player switch
            switchPlayer(true);
            break;

        case 7: //DEBUG 3: Next turn
            actionsObj.turnsPlayed++;
            actionsObj.currentHiBlind = actionsObj.checkBlinds(actionsObj.turnsPlayed);
            break;
        
        case 8: //DEBUG 4: New game
            createNewGame();
            break;
        
        case 4: //Fold button pressed
            if(actionsObj.foldAction(playerObject[currPlayer]) == false)    //If fold ask for change of round starting player
            {
                actionsObj.determineNextRoundStartingPlayer(playerObject);
                for (int i = 0; i < 4; i++) //Fetch all players data
                {
                    playerObject[i] = actionsObj.fetchPlayerData(i);
                }
            }
            playerObject[currPlayer] = actionsObj.fetchPlayerData();
            sleep(WAIT_TIME_BETWEEN_ACTIONS);
            switchPlayer(true);
            break;

        case 5: //Call or check button pressed
            if (actionsObj.highestCall - playerObject[currPlayer].moneyPut == 0)    //If checking for call or check
            {
                actionsObj.checkAction(playerObject[currPlayer]);
                playerObject[currPlayer] = actionsObj.fetchPlayerData();
                sleep(WAIT_TIME_BETWEEN_ACTIONS);
            }
            else
            {
                actionsObj.callAction(playerObject[currPlayer]);
                playerObject[currPlayer] = actionsObj.fetchPlayerData();
                sleep(WAIT_TIME_BETWEEN_ACTIONS);
            }
            switchPlayer(true);
        break;

        case 6: //Raise button pressed
            if (actionsObj.highestCall - playerObject[currPlayer].moneyPut == 0)    //If checking for bid or raise
            {
                if (actionsObj.bidAction(playerObject[currPlayer]))   //If returns without an error
                {
                    playerObject[currPlayer] = actionsObj.fetchPlayerData();    //Update player data
                    sleep(WAIT_TIME_BETWEEN_ACTIONS);
                    switchPlayer(true);
                }
            }
            else
            {
                if (actionsObj.raiseAction(playerObject[currPlayer]))   //If returns without an error
                {
                    playerObject[currPlayer] = actionsObj.fetchPlayerData();    //Update player data
                    sleep(WAIT_TIME_BETWEEN_ACTIONS);
                    switchPlayer(true);
                }
            }
            break;
        }
    }
    return 0;
}
