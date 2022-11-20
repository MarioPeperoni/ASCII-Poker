#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <string>
#include "card.h"

struct rendererStruct
{
    public:
    void bufferCard(cardStruct::Rank rank, cardStruct::Suit suit, int cardNo);
    void renderScreen();
    std::string drawCardRank(cardStruct::Rank rank, bool up);
    std::string drawDecoOnCard(cardStruct::Rank rank, int w1, int w2, int w3, int w4, int w5, std::string suitCh);
};



#endif