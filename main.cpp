#include <iostream>
#include <random>
#include <time.h>

#include "card.h"
#include "renderer.h"

using namespace std;

cardStruct::singleCard playerH[4][2];   //4 players 2 cards
cardStruct::singleCard cardsTable[5];   //5 table cards

int bufferIndex = 0;

int main()
{
    cardStruct cardObj;
    rendererStruct rednererObj;
    srand(time(0)); //Set seed of randomizer for current time
    for (int i = 0; i < 4; i++) //Generate cards for players
    {
        playerH[i][0].rank = (cardStruct::Rank)((rand() % 12) + 1);
        playerH[i][0].suit = (cardStruct::Suit)((rand() % 4) + 3);
        playerH[i][1].rank = (cardStruct::Rank)((rand() % 12) + 1);
        playerH[i][1].suit = (cardStruct::Suit)((rand() % 4) + 3);
    }
    for (int i = 0; i < 5; i++)  //Generate cards at the table
    {
        cardsTable[i].rank = (cardStruct::Rank)((rand() % 12) + 1);
        cardsTable[i].suit = (cardStruct::Suit)((rand() % 4) + 3);
    }

    system("clear");

    for (int i = 0; i < 5; i++) //Buffer all table cards
    {
        rednererObj.bufferCard(cardsTable[i].rank, cardsTable[i].suit, bufferIndex);
        bufferIndex++;  //Table cards indexes 0-4
    }
    for (int i = 1; i < 5; i++) //Buffer all player cards
    {
        rednererObj.bufferCard(playerH[i][0].rank, playerH[i][0].suit, bufferIndex);
        rednererObj.bufferCard(playerH[i][1].rank, playerH[i][1].suit, bufferIndex + 1);
        bufferIndex += 2;   //Player cards indexes 5-12
    }
    rednererObj.renderScreen(); //Render screen from buffer
    cin.get();  //Wait for user input
    return 0;
}
