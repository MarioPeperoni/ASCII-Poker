#include <iostream>
#include <string>

#include "card.h"

std::string cardStruct::translateCard(cardStruct::Rank rank)
{
    switch ((int)rank)
    {
    case 2:
        return "TWO";
        break;
    case 3:
        return "THREE";
        break;
    case 4:
        return "FOUR";
        break;
    case 5:
        return "FIVE";
        break;
    case 6:
        return "SIX";
        break;
    case 7:
        return "SEVEN";
        break;
    case 8:
        return "EIGHT";
        break;
    case 9:
        return "NINE";
        break;
    case 10:
        return "TEN";
        break;
    case 11:
        return "JACK";
        break;
    case 12:
        return "QUEEN";
        break;
    case 13:
        return "KING";
        break;
    case 14:
        return "ACE";
        break;
    }
    return "ERROR";
}

std::string cardStruct::translateCard(cardStruct::Suit suit)
{
    switch ((int)suit)
    {
    case 3:
        return "HEARTS";
        break;
    case 4:
        return "DIAMONDS";
        break;
    case 5:
        return "CLUBS";
        break;
    case 6:
        return "SPADES";
        break;
    }
    return "ERROR";
}