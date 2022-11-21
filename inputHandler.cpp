#include <iostream>
#include <curses.h>
#include <string>

#include "inputHandler.h"

using namespace std;

/*
RETURN CODES:
0 - Succesfully registerd key press
1 - Error
2 - Start new game trigger
*/

int inputHandlerStruct::getInput()
{
    string input;   //String storing input from keyboard
    cin >> input;   //Player input
    switch (input[0])
    {
    case 'a':   //Left key press
        if (inputHandlerStruct::cursorPos == 1) //If index is at its min position
        {
            inputHandlerStruct::cursorPos = 3;  //Loop cursor position index
        }
        else
        {
            inputHandlerStruct::cursorPos--;    //Change cursor pos -1
        }
        return 0;
        break;

    case 'd':   //Right key press
        if (inputHandlerStruct::cursorPos == 3) //If index is at its max position
        {
            inputHandlerStruct::cursorPos = 1;  //Loop cursor position index
        }
        else
        {
            inputHandlerStruct::cursorPos++;    //Change cursor pos +1
        }
        return 0;
        break;

    case 'n':   //New game button trigger
        return 2;

    default:
        return 1;   //Return error code if not found in switch
        break;
    }
    return 1;   //Return error code if out of switch
}