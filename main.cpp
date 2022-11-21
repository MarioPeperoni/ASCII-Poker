#include <iostream>
#include <random>
#include <time.h>
#include <curses.h>

#include "card.h"
#include "renderer.h"
#include "inputHandler.h"
#include "playerData.h"

using namespace std;

playerDataStruct playerObject[4];   //Player object that stores all player values
cardStruct::singleCard cardsTable[5];   //5 table cards

int bufferIndex = 0;    //Buffer index
bool initDefNames = true;   //Bool for creating default names for players

int main()
{
    inputHandlerStruct inputHandelerObj;
    cardStruct cardObj;
    rendererStruct rednererObj;
    srand(time(0)); //Set seed of randomizer for current time
    //=====================================================GAME INIT====================================================
    for (int i = 0; i < 4; i++) //Generate cards for players
    {
        playerObject[i].playerHand[0].rank = (cardStruct::Rank)((rand() % 12) + 1);
        playerObject[i].playerHand[0].suit = (cardStruct::Suit)((rand() % 4) + 3);
        playerObject[i].playerHand[1].rank = (cardStruct::Rank)((rand() % 12) + 1);
        playerObject[i].playerHand[1].suit = (cardStruct::Suit)((rand() % 4) + 3);
    }
    for (int i = 0; i < 5; i++)  //Generate cards at the table
    {
        cardsTable[i].rank = (cardStruct::Rank)((rand() % 12) + 1);
        cardsTable[i].suit = (cardStruct::Suit)((rand() % 4) + 3);
    }
    for (int i = 0; i < 5; i++) //Buffer all table cards
    {
        rednererObj.bufferCard(cardsTable[i].rank, cardsTable[i].suit, bufferIndex);
        bufferIndex++;  //Table cards indexes 0-4
    }
    for (int i = 1; i < 5; i++) //Buffer all player cards
    {
        rednererObj.bufferCard(playerObject[i].playerHand[0].rank, playerObject[i].playerHand[0].suit, bufferIndex);
        rednererObj.bufferCard(playerObject[i].playerHand[1].rank, playerObject[i].playerHand[1].suit, bufferIndex + 1);
        bufferIndex += 2;   //Player cards indexes 5-12
    }
    if (initDefNames)   //Set default player names "Player (no)"
    {
        for (int i = 0; i < 4; i++)
        {
            playerObject[i].playerName = "Player " + to_string(i + 1);
        }
    }
    
    //===================================================RENDER LOOP==================================================
    while (true)
    {
        rednererObj.renderScreen(inputHandelerObj.cursorPos, playerObject, 1); //Render screen from buffer
        inputHandelerObj.getInput();
    }
    return 0;
}
