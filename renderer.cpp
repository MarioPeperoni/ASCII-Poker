#include <iostream>
#include <string>

#include "renderer.h"
#include "card.h"
#include "inputHandler.h"

#define WINDOW_WIDTH 160
#define WINDOW_HEIGHT 50

#define UI_BUTTON_ROW_ID 42

#define UI_BUTTON_1_START_POS 10
#define UI_BUTTON_2_START_POS 30
#define UI_BUTTON_3_START_POS 50

using namespace std;

inputHandlerStruct inputHandlerStructObj;
rendererStruct rendererStructVar;
std::string cardBuff[12][11];   //Card buffer stores all visuals of cards now in game 0-4 table cards 5-6 p1 7-8 p2 9-10 p3 11-12 p4

std::string UIBuff[WINDOW_WIDTH][WINDOW_HEIGHT];    //UI Buffer stores all UI items

int tempCursorLogic;


string rendererStruct::drawDecoOnCard(cardStruct::Rank rank, int w1, int w2, int w3, int w4, int w5, string suitCh) //Insert card decoration while buffering graphics
{
    if ((int)rank == w1 || (int)rank == w2 || (int)rank == w3 || (int)rank == w4 || (int)rank == w5)
    {
        return suitCh;
    }
    return " ";
}

string rendererStruct::drawCardRank(cardStruct::Rank rank, bool up) //Outputs visual representation of card rank for drawing in buffer
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

void SetCursorPos(int XPos, int YPos)   //Sets cursor position on console screen
{
    printf("\033[%d;%dH", YPos+1, XPos+1);
}

void rendererStruct::bufferCard(cardStruct::Rank rank, cardStruct::Suit suit, int cardNo)   //Buffers card
{
    //Stores suit icon
    string suitChar;
    switch ((int)suit)
    {
    case 3:
        suitChar = "\x1b[31m♥\x1b[0m"; //\x1b[31m Red colour
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

    //Buffer card graphics
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

void rendererStruct::deleteBuffer() //Clears buffer
{
    for (int y = 0; y < WINDOW_HEIGHT; y++)
    {
        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            UIBuff[x][y] = "";
        }
    }
}

void rendererStruct::renderScreen(int cursorPos)
{   
    system("clear");
    //=================================================HUD=================================================
    //Draw HUD Frame
    SetCursorPos(0,36);
    cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓";
    for (int i = 37; i < 41; i++)
    {
        SetCursorPos(26,i);
        cout << "█";
    }

    //Draws down UI Bar
    SetCursorPos(3,38);
    cout << "Current Pot: 100000$";
    SetCursorPos(0,40);
    for (int i = 0; i < WINDOW_WIDTH; i++)
    {
        cout << "█";
    }

    //Draw buttons
    SetCursorPos(UI_BUTTON_1_START_POS, UI_BUTTON_ROW_ID);  
    cout << "FOLD";
    SetCursorPos(UI_BUTTON_2_START_POS, UI_BUTTON_ROW_ID);
    cout << "CALL";
    SetCursorPos(UI_BUTTON_3_START_POS, UI_BUTTON_ROW_ID);
    cout << "RAISE";

    //Draw graphic representation of selected button
    switch (cursorPos)
    {
    case 1:
        SetCursorPos(UI_BUTTON_1_START_POS - 7, UI_BUTTON_ROW_ID - 1);
        cout << "##################";
        SetCursorPos(UI_BUTTON_1_START_POS - 7, UI_BUTTON_ROW_ID + 1);
        cout << "##################";
        SetCursorPos(UI_BUTTON_1_START_POS - 7, UI_BUTTON_ROW_ID);
        cout << "#";
        SetCursorPos(UI_BUTTON_1_START_POS + 10, UI_BUTTON_ROW_ID);
        cout << "#";
        break;
    case 2:
        SetCursorPos(UI_BUTTON_2_START_POS - 7, UI_BUTTON_ROW_ID - 1);
        cout << "##################";
        SetCursorPos(UI_BUTTON_2_START_POS - 7, UI_BUTTON_ROW_ID + 1);
        cout << "##################";
        SetCursorPos(UI_BUTTON_2_START_POS - 7, UI_BUTTON_ROW_ID);
        cout << "#";
        SetCursorPos(UI_BUTTON_2_START_POS + 10, UI_BUTTON_ROW_ID);
        cout << "#";
        break;
    case 3:
        SetCursorPos(UI_BUTTON_3_START_POS - 7, UI_BUTTON_ROW_ID - 1);
        cout << "##################";
        SetCursorPos(UI_BUTTON_3_START_POS - 7, UI_BUTTON_ROW_ID + 1);
        cout << "##################";
        SetCursorPos(UI_BUTTON_3_START_POS - 7, UI_BUTTON_ROW_ID);
        cout << "#";
        SetCursorPos(UI_BUTTON_3_START_POS + 10, UI_BUTTON_ROW_ID);
        cout << "#";
        break;
    }

    //================================================TABLE=================================================
    SetCursorPos(0,10); //Draws cards
    for (int i = 0; i < 11; i++)    //Size of card is 11 rows
    {
        for (int j = 0; j < 5; j++) //Table cards index
        {
            cout << cardBuff[j][i];
        }
        cout << endl;
    }
    for (int i = 0; i < 11; i++)    //Size of card is 11 rows
    {
        for (int j = 5; j < 7; j++) //Player 1 buffer indexes
        {
            cout << cardBuff[j][i];
        }
        cout << endl;
    }
    SetCursorPos(0 ,WINDOW_HEIGHT); //Reset cursor to bottom of window
    cout << " ";    //For setting max widnow height
    SetCursorPos(0 ,WINDOW_HEIGHT - 2); //Set cursor for input
}