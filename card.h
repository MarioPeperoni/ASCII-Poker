#ifndef CARD_H
#define CARD_H

struct cardStruct
{
    public:
    enum Rank
    {
        ACE = 1,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING
    };

    enum Suit
    {
        HEARTS = 3,
        DIAMONDS,
        CLUBS,
        SPADES
    };
};


#endif