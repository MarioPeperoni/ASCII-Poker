#include <iostream>
#include <string>

#include "renderer.h"
#include "card.h"
#include "inputHandler.h"
#include "playerData.h"

#define WINDOW_WIDTH 160
#define WINDOW_HEIGHT 50

#define UI_BUTTON_ROW_ID 42

#define UI_BUTTON_1_START_POS 10
#define UI_BUTTON_2_START_POS 30
#define UI_BUTTON_3_START_POS 50

#define UI_PLAYER_1_TAG_POS 25
#define UI_PLAYER_2_TAG_POS 55
#define UI_PLAYER_3_TAG_POS 85
#define UI_PLAYER_4_TAG_POS 115

#define PLAYER_HAND_RENDER_POS_X 60
#define PLAYER_HAND_RENDER_POS_Y 30

#define TABLE_CARDS_RENDER_POS_X 35
#define TABLE_CARDS_RENDER_POS_Y 15

using namespace std;

inputHandlerStruct inputHandlerStructObj;
rendererStruct rendererStructVar;
std::string cardBuff[12][11];   //Card buffer stores all visuals of cards now in game 0-4 table cards 5-6 p1 7-8 p2 9-10 p3 11-12 p4

std::string UIBuff[WINDOW_WIDTH][WINDOW_HEIGHT];    //UI Buffer stores all UI items

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

void rendererStruct::renderScreen(int cursorPos, playerDataStruct players[4], int currentPlayer)
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
    SetCursorPos(0,44);
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

    //Draw players data on top of the screen
    //Player 1
    if(players[0].isCurrentPlayer){SetCursorPos(UI_PLAYER_1_TAG_POS, 0); cout << "║                  ║";}
    SetCursorPos(UI_PLAYER_1_TAG_POS, 0 + (int)players[0].isCurrentPlayer);
    cout << "╚══════════════════╝";
    SetCursorPos(UI_PLAYER_1_TAG_POS + ((20 - players[0].playerName.length()) / 2), 1 + (int)players[0].isCurrentPlayer);
    cout << players[0].playerName;
    SetCursorPos(UI_PLAYER_1_TAG_POS + ((20 - to_string(players[0].money).length()) / 2), 2 + (int)players[0].isCurrentPlayer);
    cout << players[0].money;

    //Player 2
    if(players[1].isCurrentPlayer){SetCursorPos(UI_PLAYER_2_TAG_POS, 0); cout << "║                  ║";}
    SetCursorPos(UI_PLAYER_2_TAG_POS, 0 + (int)players[1].isCurrentPlayer);
    cout << "╚══════════════════╝";
    SetCursorPos(UI_PLAYER_2_TAG_POS + ((20 - players[1].playerName.length()) / 2), 1 + (int)players[1].isCurrentPlayer);
    cout << players[1].playerName;
    SetCursorPos(UI_PLAYER_2_TAG_POS + ((20 - to_string(players[1].money).length()) / 2), 2 + (int)players[1].isCurrentPlayer);
    cout << players[1].money;

    //Player 3
    if(players[2].isCurrentPlayer){SetCursorPos(UI_PLAYER_3_TAG_POS, 0); cout << "║                  ║";}
    SetCursorPos(UI_PLAYER_3_TAG_POS, 0 + (int)players[2].isCurrentPlayer);
    cout << "╚══════════════════╝";
    SetCursorPos(UI_PLAYER_3_TAG_POS + ((20 - players[2].playerName.length()) / 2), 1 + (int)players[2].isCurrentPlayer);
    cout << players[2].playerName;
    SetCursorPos(UI_PLAYER_3_TAG_POS + ((20 - to_string(players[2].money).length()) / 2), 2 + (int)players[2].isCurrentPlayer);
    cout << players[2].money;

    //Player 4
    if(players[3].isCurrentPlayer){SetCursorPos(UI_PLAYER_4_TAG_POS, 0); cout << "║                  ║";}
    SetCursorPos(UI_PLAYER_4_TAG_POS, 0 + (int)players[3].isCurrentPlayer);
    cout << "╚══════════════════╝";
    SetCursorPos(UI_PLAYER_4_TAG_POS + ((20 - players[3].playerName.length()) / 2), 1 + (int)players[3].isCurrentPlayer);
    cout << players[3].playerName;
    SetCursorPos(UI_PLAYER_4_TAG_POS + ((20 - to_string(players[3].money).length()) / 2), 2 + (int)players[3].isCurrentPlayer);
    cout << players[3].money;


    //================================================TABLE=================================================
    SetCursorPos(TABLE_CARDS_RENDER_POS_X, TABLE_CARDS_RENDER_POS_Y); //Draws table cards
    for (int i = -1; i < 11; i++)    //Size of card is 11 rows
    {
        for (int j = 0; j < 5; j++) //Table cards index
        {
            cout << cardBuff[j][i];
        }
        SetCursorPos(TABLE_CARDS_RENDER_POS_X, TABLE_CARDS_RENDER_POS_Y + i);
    }
    SetCursorPos(PLAYER_HAND_RENDER_POS_X, PLAYER_HAND_RENDER_POS_Y);
    for (int i = -1; i < 11; i++)    //Size of card is 11 rows
    {
        for (int j = 5; j < 7; j++) //Player 1 buffer indexes
        {
            cout << cardBuff[j][i];
        }
        SetCursorPos(PLAYER_HAND_RENDER_POS_X, PLAYER_HAND_RENDER_POS_Y + i);
    }

    SetCursorPos(0 ,WINDOW_HEIGHT); //Reset cursor to bottom of window
    cout << " ";    //For setting max widnow height
    SetCursorPos(0 ,WINDOW_HEIGHT - 2); //Set cursor for input
}