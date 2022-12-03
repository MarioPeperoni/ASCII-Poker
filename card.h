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
        ACE = 14
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

    struct pairs
    {
        int noOfPairs = 0;  //No of pairs
        Rank pairs[4];  //Pairs stored max 4 pairs
    };

    std::string translateCard(cardStruct::Rank);
    std::string translateCard(cardStruct::Suit);
};
#endif