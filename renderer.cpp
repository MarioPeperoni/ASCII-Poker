#include <iostream>
#include <string>

#include "renderer.h"
#include "card.h"
#include "inputHandler.h"
#include "playerData.h"
#include "gameActions.h"

using namespace std;

inputHandlerStruct inputHandlerStructObj;
rendererStruct rendererStructVar;

std::string cardBuff[13][11];   //Card buffer stores all visuals of cards now in game 0-4 table cards 5-6 p1 7-8 p2 9-10 p3 11-12 p4

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
    case 14:
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

void rendererStruct::SetCursorPos(int XPos, int YPos)   //Sets cursor position on console screen
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

void rendererStruct::drawPotGraphics()
{
    //Rozpoczyna od 3, 12
    //Wymiar 60 x 24
    SetCursorPos(G_POT_START_POS_X, G_POT_START_POS_Y);
    for (int i = 0; i < G_POT_HEIGHT; i++)
    {
        for (int j = 0; j < G_POT_WIDTH; j++)
        {
            cout << "░";
        }
        SetCursorPos(G_POT_START_POS_X, G_POT_START_POS_Y + i);
    }
}
void rendererStruct::drawEndRoundScreen(playerDataStruct playerWon)
{
    SetCursorPos((WINDOW_WIDTH/2) - 22, WINDOW_HEIGHT/2 - 1);
    cout << "╔═══════════════════════════════════════════╗";
    SetCursorPos((WINDOW_WIDTH/2) - 22, WINDOW_HEIGHT/2);
    cout << "║                                           ║";
    string printString = playerWon.playerName + " won with " + playerWon.setName;
    SetCursorPos((WINDOW_WIDTH/2) - printString.length() / 2, WINDOW_HEIGHT/2);
    cout << printString;
    SetCursorPos((WINDOW_WIDTH/2) - 22, WINDOW_HEIGHT/2 + 1);
    cout << "║ Press any button to play another round... ║";
    SetCursorPos((WINDOW_WIDTH/2) - 22, WINDOW_HEIGHT/2 + 2);
    cout << "╚═══════════════════════════════════════════╝";
    cin.get();
    cin.get();
}

void rendererStruct::renderScreen(int cursorPos, playerDataStruct players[4], int currentPlayer, gameActionsStruct actionObj)
{   
    system("clear");
    drawPotGraphics();
    //=================================================HUD=================================================

    //Draws down UI Bar
    SetCursorPos(UI_CURRENT_POT_TEXT_X, UI_CURRENT_POT_TEXT_Y);
    cout << "Current Pot: " + to_string(actionObj.currentPot) + "$";    //Prints current pot value

    //Bottom bars
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

    //===============================================POP TEXT===================================================

    //Last action text
    SetCursorPos(UI_TEMP_HAND_NAME, UI_BUTTON_ROW_ID);
    cout << players[currentPlayer].setName;

    //Draw custom UI center screen pop up
    if (actionObj.bigActionText != "" || true)  //Draw border always
    {
        SetCursorPos(0, 8);
        for (int i = 0; i < WINDOW_WIDTH; i++) {cout << "=";}   //Draw border
        SetCursorPos(0, 10);
        for (int i = 0; i < WINDOW_WIDTH; i++) {cout << "=";}   //Draw border
    }
    SetCursorPos((WINDOW_WIDTH/2) - (actionObj.bigActionText.length() / 2) - 3, 9); //Draw text
    cout << actionObj.bigActionText;    //Draw UI center text from action struct


    //=================================================BUTTONS=================================================
    //Draw buttons
    SetCursorPos(UI_BUTTON_1_START_POS, UI_BUTTON_ROW_ID);  
    cout << "FOLD";
    SetCursorPos(UI_BUTTON_2_START_POS, UI_BUTTON_ROW_ID);
    actionObj.highestCall - players[currentPlayer].moneyPut == 0 ? cout << "CHECK" : cout << "CALL";
    SetCursorPos(UI_BUTTON_3_START_POS, UI_BUTTON_ROW_ID);
    actionObj.highestCall - players[currentPlayer].moneyPut == 0 ? cout << "BID" : cout << "RAISE";

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

        //Draw call button money value frame
        SetCursorPos(UI_BUTTON_2_START_POS - 3, UI_BUTTON_ROW_ID - 3);
        cout << "║";
        SetCursorPos(UI_BUTTON_2_START_POS + 6, UI_BUTTON_ROW_ID - 3);
        cout << "║";
        SetCursorPos(UI_BUTTON_2_START_POS - 3, UI_BUTTON_ROW_ID - 4);
        cout << "╔════════╗";
        SetCursorPos((UI_BUTTON_2_START_POS - 2) - ((to_string(actionObj.highestCall).length() + 1) / 2) + 4, UI_BUTTON_ROW_ID - 3);
        cout << to_string(actionObj.highestCall - players[currentPlayer].moneyPut) + "$";   //Draw call value

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

         //Draw raise button money value frame
        SetCursorPos(UI_BUTTON_3_START_POS - 3, UI_BUTTON_ROW_ID - 3);
        cout << "║";
        SetCursorPos(UI_BUTTON_3_START_POS + 6, UI_BUTTON_ROW_ID - 3);
        cout << "║";
        SetCursorPos(UI_BUTTON_3_START_POS - 3, UI_BUTTON_ROW_ID - 4);
        cout << "║";
        SetCursorPos(UI_BUTTON_3_START_POS + 6, UI_BUTTON_ROW_ID - 4);
        cout << "║";
        SetCursorPos(UI_BUTTON_3_START_POS - 3, UI_BUTTON_ROW_ID - 5);
        cout << "╔════════╗";
        SetCursorPos(UI_BUTTON_3_START_POS - 1, UI_BUTTON_ROW_ID - 4);
        cout << "VALUE:";
        SetCursorPos(UI_BUTTON_3_START_POS - 1, UI_BUTTON_ROW_ID - 3);
        cout << "▒▒▒▒▒▒";

        break;
    }


    //=================================================PLAYERS=================================================
    //Draw players data on top of the screen
    //Player 1
    if(players[0].isCurrentPlayer){SetCursorPos(UI_PLAYER_1_TAG_POS, 0); cout << "║                  ║";}
    SetCursorPos(UI_PLAYER_1_TAG_POS, 0 + (int)players[0].isCurrentPlayer);
    cout << "╚══════════════════╝";
    SetCursorPos(UI_PLAYER_1_TAG_POS + ((20 - players[0].playerName.length()) / 2), 1 + (int)players[0].isCurrentPlayer);
    cout << players[0].playerName;
    SetCursorPos(UI_PLAYER_1_TAG_POS + ((20 - to_string(players[0].money).length()) / 2), 2 + (int)players[0].isCurrentPlayer);
    cout << players[0].money << "$";
    SetCursorPos(UI_PLAYER_1_TAG_POS + ((20 - players[0].lastPlayerAction.length()) / 2), 3 + (int)players[0].isCurrentPlayer);
    cout << players[0].lastPlayerAction;

    //Player 2
    if(players[1].isCurrentPlayer){SetCursorPos(UI_PLAYER_2_TAG_POS, 0); cout << "║                  ║";}
    SetCursorPos(UI_PLAYER_2_TAG_POS, 0 + (int)players[1].isCurrentPlayer);
    cout << "╚══════════════════╝";
    SetCursorPos(UI_PLAYER_2_TAG_POS + ((20 - players[1].playerName.length()) / 2), 1 + (int)players[1].isCurrentPlayer);
    cout << players[1].playerName;
    SetCursorPos(UI_PLAYER_2_TAG_POS + ((20 - to_string(players[1].money).length()) / 2), 2 + (int)players[1].isCurrentPlayer);
    cout << players[1].money << "$";
    SetCursorPos(UI_PLAYER_2_TAG_POS + ((20 - players[1].lastPlayerAction.length()) / 2), 3 + (int)players[1].isCurrentPlayer);
    cout << players[1].lastPlayerAction;

    //Player 3
    if(players[2].isCurrentPlayer){SetCursorPos(UI_PLAYER_3_TAG_POS, 0); cout << "║                  ║";}
    SetCursorPos(UI_PLAYER_3_TAG_POS, 0 + (int)players[2].isCurrentPlayer);
    cout << "╚══════════════════╝";
    SetCursorPos(UI_PLAYER_3_TAG_POS + ((20 - players[2].playerName.length()) / 2), 1 + (int)players[2].isCurrentPlayer);
    cout << players[2].playerName;
    SetCursorPos(UI_PLAYER_3_TAG_POS + ((20 - to_string(players[2].money).length()) / 2), 2 + (int)players[2].isCurrentPlayer);
    cout << players[2].money << "$";
    SetCursorPos(UI_PLAYER_3_TAG_POS + ((20 - players[2].lastPlayerAction.length()) / 2), 3 + (int)players[2].isCurrentPlayer);
    cout << players[2].lastPlayerAction;

    //Player 4
    if(players[3].isCurrentPlayer){SetCursorPos(UI_PLAYER_4_TAG_POS, 0); cout << "║                  ║";}
    SetCursorPos(UI_PLAYER_4_TAG_POS, 0 + (int)players[3].isCurrentPlayer);
    cout << "╚══════════════════╝";
    SetCursorPos(UI_PLAYER_4_TAG_POS + ((20 - players[3].playerName.length()) / 2), 1 + (int)players[3].isCurrentPlayer);
    cout << players[3].playerName;
    SetCursorPos(UI_PLAYER_4_TAG_POS + ((20 - to_string(players[3].money).length()) / 2), 2 + (int)players[3].isCurrentPlayer);
    cout << players[3].money << "$";
    SetCursorPos(UI_PLAYER_4_TAG_POS + ((20 - players[3].lastPlayerAction.length()) / 2), 3 + (int)players[3].isCurrentPlayer);
    cout << players[3].lastPlayerAction;


    //================================================BUFFER CARDS=================================================
    SetCursorPos(((WINDOW_WIDTH / 2) - 12) - (8 * (actionObj.gameState - 1) - TABLE_CARDS_RENDER_POS_X), TABLE_CARDS_RENDER_POS_Y); //Draws table cards
    for (int i = -1; i < 11; i++)    //Size of card is 11 rows
    {
        for (int j = 0; j < actionObj.gameState; j++) //Table cards index
        {
            cout << cardBuff[j][i];
        }
        SetCursorPos(((WINDOW_WIDTH / 2) - 12) - (8 * (actionObj.gameState - 1) - TABLE_CARDS_RENDER_POS_X), TABLE_CARDS_RENDER_POS_Y + i);
    }
    SetCursorPos(PLAYER_HAND_RENDER_POS_X, PLAYER_HAND_RENDER_POS_Y);
    for (int i = -1; i < 11; i++)    //Size of card is 11 rows
    {
        switch (currentPlayer)
        {
        case 0:
            for (int j = 5; j < 7; j++) //Player 1 buffer indexes
            {
                cout << cardBuff[j][i];
            }
            break;

        case 1:
            for (int j = 7; j < 9; j++) //Player 2 buffer indexes
            {
                cout << cardBuff[j][i];
            }
            break;

        case 2:
            for (int j = 9; j < 11; j++) //Player 3 buffer indexes
            {
                cout << cardBuff[j][i];
            }
            break;

        case 3:
            for (int j = 11; j < 13; j++) //Player 4 buffer indexes
            {
                cout << cardBuff[j][i];
            }
            break;
        default:
            break;
        }
        SetCursorPos(PLAYER_HAND_RENDER_POS_X, PLAYER_HAND_RENDER_POS_Y + i);
    }

    SetCursorPos(0 ,WINDOW_HEIGHT); //Reset cursor to bottom of window
    cout << " ";    //For setting max widnow height
    SetCursorPos(0 ,WINDOW_HEIGHT - 2); //Set cursor for input
}

void rendererStruct::renderPlayerChangeScreen(int currentPlayer)
{
    system("clear");
    SetCursorPos((WINDOW_WIDTH/2) - 8, WINDOW_HEIGHT/2);
    cout << "[Player " + to_string(currentPlayer + 1) + " turn]";
    SetCursorPos((WINDOW_WIDTH/2) - 16, WINDOW_HEIGHT/2 + 1);
    cout << "Press any button to continue...";
    cin.get();
    cin.get();
}