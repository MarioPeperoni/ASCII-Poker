#include <iostream>
#include <curses.h>
#include <string>

#include "inputHandler.h"

using namespace std;

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

    case '1':   //DEBUG 1: Inc Game state
        return 2;
    
    case '2':   //DEBUG 2: Player switch
        return 3;
    
    case '3':   //DEBUG 3: Next turn
        return 7;

    case '4':   //DEBUG 4: New game
        return 8;

    case 'p':
        switch (inputHandlerStruct::cursorPos)
        {
        case 1:
            return 4;   //Fold button pressed trigger
            break;
        case 2:
            return 5;   //Call button pressed trigger
            break;
        case 3:
            return 6;   //Raise button pressed trigger
            break;
        default:
            return 1;   //Return error code if selected button is not existing
            break;
        }

    default:
        return 1;   //Return error code if not found in switch
        break;
    }
    return 1;   //Return error code if out of switch
}