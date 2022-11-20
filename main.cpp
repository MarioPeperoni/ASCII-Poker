#include <iostream>
#include <random>
#include <time.h>

#include "card.h"
#include "renderer.h"

#define WINDOW_WIDTH 160
#define WINDOW_HEIGHT 50

using namespace std;

int main()
{
    cardStruct cardObj;
    rendererStruct rednererObj;
    srand(time(0));
    for (int i = 0; i < 2; i++)
    {
        rednererObj.bufferCard((cardStruct::Rank)((rand() % 12)+1),(cardStruct::Suit)((rand() % 4) + 3), i);
    }
    rednererObj.renderScreen();
    return 0;
}
