#include <iostream>

using namespace std;

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

string cardBuff[11];

string drawDecoOnCard(Rank rank, int w1, int w2, int w3, int w4, int w5, string suitCh)
{
    if ((int)rank == w1 || (int)rank == w2 || (int)rank == w3 || (int)rank == w4 || (int)rank == w5)
    {
        return suitCh;
    }
    return " ";
}

string drawCardRank(Rank rank, bool up)
{
    string result;
    switch ((int)rank)
    {
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

void bufferCard(Rank rank, Suit suit)
{
    string suitChar;
    switch ((int)suit)
    {
    case 3:
        suitChar = "♥";
        break;
    case 4:
        suitChar = "♦";
        break;
    case 5:
        suitChar = "♣";
        break;
    case 6:
        suitChar = "♠";
        break;
    }

    cardBuff[0] = "╔═══════════════╗";  //Row 1
    cardBuff[1] = "║ " + suitChar + "             ║";     //Row 2
    cardBuff[2] = "║" + drawCardRank(rank, true) + "  " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "     " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "    ║";      //Row 3
    cardBuff[3] = "║    " + drawDecoOnCard(rank, 4, 5, 6, 7, 8, suitChar) + "  " + drawDecoOnCard(rank, 2, 3, 10, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 4, 5, 6, 7, 8, suitChar)+ "    ║";  //Row 4
    cardBuff[4] = "║    " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 7, 8, 0, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "    ║";                      //Row 5
    cardBuff[5] = "║    " + drawDecoOnCard(rank, 6, 7, 8, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 3, 5, 9, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 6, 7, 8, 0, 0, suitChar) + "    ║";   //Row 6
    cardBuff[6] = "║    " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 0, 8, 0, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "    ║";                        //Row 7
    cardBuff[7] = "║    " + drawDecoOnCard(rank, 4, 5, 6, 7, 8, suitChar) + "  " + drawDecoOnCard(rank, 2, 3, 10, 0, 0, suitChar) + "  " + drawDecoOnCard(rank, 4, 5, 6, 7, 8, suitChar) + "    ║";   //Row 8
    cardBuff[8] = "║    " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "     " + drawDecoOnCard(rank, 9, 10, 0, 0, 0, suitChar) + "  " + suitChar + " ║";     //Row 9
    cardBuff[9] = "║             " + drawCardRank(rank, false) + "║";   //Row 10
    cardBuff[10] = "╚═══════════════╝";                      //Row 11
}


int main()
{
    
    
    
    return 0;
}
