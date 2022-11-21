#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

struct inputHandlerStruct
{
    public:
    int cursorPos = 1;  //Cursor position index for buttons
    int getInput();     //Input loop function
};

#endif