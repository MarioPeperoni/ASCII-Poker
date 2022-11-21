#include <iostream>
#include <curses.h>
#include <string>

#include "inputHandler.h"

using namespace std;

void inputHandlerStruct::getInput()
{
    string input;
    cin >> input;
    switch (input[0])
    {
    case 'a':
        if (inputHandlerStruct::cursorPos == 1)
        {
            inputHandlerStruct::cursorPos = 3;
        }
        else
        {
            inputHandlerStruct::cursorPos--;
        }
        break;
    case 'd':
        if (inputHandlerStruct::cursorPos == 3)
        {
            inputHandlerStruct::cursorPos = 1;
        }
        else
        {
            inputHandlerStruct::cursorPos++;
        }
        break;
    default:
        break;
    }
}