#ifndef CARD_H
#define CARD_H

struct cardStruct
{
    public:
    enum Rank
    {
        TWO = 2,
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
        KING,
        ACE
    };

    enum Suit
    {
        HEARTS = 3,
        DIAMONDS,
        CLUBS,
        SPADES
    };

    struct singleCard
    {
        Rank rank;
        Suit suit;
    };
};
#endif