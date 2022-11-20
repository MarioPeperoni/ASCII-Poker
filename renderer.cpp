#include <iostream>
#include <string>

#include "renderer.h"
#include "card.h"

using namespace std;

rendererStruct rendererStructVar;
std::string cardBuff[2][11];


string rendererStruct::drawDecoOnCard(cardStruct::Rank rank, int w1, int w2, int w3, int w4, int w5, string suitCh)
{
    if ((int)rank == w1 || (int)rank == w2 || (int)rank == w3 || (int)rank == w4 || (int)rank == w5)
    {
        return suitCh;
    }
    return " ";
}

string rendererStruct::drawCardRank(cardStruct::Rank rank, bool up)
{
    string result;
    switch ((int)rank)
    {
    case 1:
        result = up ? " A" : "A ";
        break;
    case 10:
        return "10";
        break;
    case 11:
        result = up ? " J" : "J ";
        break;
    case 12:
        result = up ? " Q" : "Q ";
        break;
    case 13:
        result = up ? " K" : "K ";
        break;
    
    default:
        result = up ? " " + to_string((int)rank) : to_string((int)rank) + " ";
        break;
    }
    return result;
    
}

void rendererStruct::bufferCard(cardStruct::Rank rank, cardStruct::Suit suit, int cardNo)
{
    string suitChar;
    switch ((int)suit)
    {
    case 3:
        suitChar = "\x1b[31m♥\x1b[0m";
        break;
    case 4:
        suitChar = "\x1b[31m♦\x1b[0m";
        break;
    case 5:
        suitChar = "♣";
        break;
    case 6:
        suitChar = "♠";
        break;
    }

    cardBuff[cardNo][0] = "╔═══════════════╗";  //Row 1
    cardBuff[cardNo][1] = "║ " + suitChar + "             ║";     //Row 2
    cardBuff[cardNo][2] = "║" + drawCardRank(rank, true) + "  " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "     " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "    ║";      //Row 3
    cardBuff[cardNo][3] = "║    " + drawDecoOnCard(rank, 4, 5, 6, 7, 8, suitChar) + "  " + drawDecoOnCard(rank, 2, 3, 10, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 4, 5, 6, 7, 8, suitChar)+ "    ║";  //Row 4
    cardBuff[cardNo][4] = "║    " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 7, 8, 0, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "    ║";                      //Row 5
    cardBuff[cardNo][5] = "║    " + drawDecoOnCard(rank, 6, 7, 8, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 3, 5, 9, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 6, 7, 8, 0, 0, suitChar) + "    ║";   //Row 6
    cardBuff[cardNo][6] = "║    " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 0, 8, 0, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "    ║";                        //Row 7
    cardBuff[cardNo][7] = "║    " + drawDecoOnCard(rank, 4, 5, 6, 7, 8, suitChar) + "  " + drawDecoOnCard(rank, 2, 3, 10, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 4, 5, 6, 7, 8, suitChar) + "    ║";   //Row 8
    cardBuff[cardNo][8] = "║    " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "     " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "  " + suitChar + " ║";     //Row 9
    cardBuff[cardNo][9] = "║             " + drawCardRank(rank, false) + "║";   //Row 10
    cardBuff[cardNo][10] = "╚═══════════════╝";                      //Row 11
}

void rendererStruct::renderScreen()
{
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << cardBuff[j][i];
        }
        cout << endl;
        
    }
}