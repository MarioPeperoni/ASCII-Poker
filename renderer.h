#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include "card.h"
#include "playerData.h"
#include "gameActions.h"

#define WINDOW_WIDTH 160
#define WINDOW_HEIGHT 50

#define UI_BUTTON_ROW_ID 42

#define UI_BUTTON_1_START_POS 10
#define UI_BUTTON_2_START_POS 30
#define UI_BUTTON_3_START_POS 50

#define UI_TEMP_HAND_NAME 96
#define UI_CALL_INPUT_BOX_POS_X 49
#define UI_CALL_INPUT_BOX_POS_Y 39

#define UI_CURRENT_POT_TEXT_X 22
#define UI_CURRENT_POT_TEXT_Y 36

#define G_POT_START_POS_X 3
#define G_POT_START_POS_Y 12
#define G_POT_WIDTH 60
#define G_POT_HEIGHT 24

#define UI_PLAYER_1_TAG_POS 25
#define UI_PLAYER_2_TAG_POS 55
#define UI_PLAYER_3_TAG_POS 85
#define UI_PLAYER_4_TAG_POS 115

#define PLAYER_HAND_RENDER_POS_X 95
#define PLAYER_HAND_RENDER_POS_Y 29

#define TABLE_CARDS_RENDER_POS_X 33
#define TABLE_CARDS_RENDER_POS_Y 15

struct rendererStruct
{
    public:
    void drawPotGraphics();
    void bufferCard(cardStruct::Rank rank, cardStruct::Suit suit, int cardNo);
    void renderScreen(int cursorPos, playerDataStruct players[4], int currentPlayer, gameActionsStruct actionObj);
    void renderPlayerChangeScreen(int currentPlayer);
    std::string drawCardRank(cardStruct::Rank rank, bool up);
    std::string drawDecoOnCard(cardStruct::Rank rank, int w1, int w2, int w3, int w4, int w5, std::string suitCh);
    void SetCursorPos(int XPos, int YPos);
};
#endif