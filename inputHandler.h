#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

struct inputHandlerStruct
{
    public:
    int cursorPos = 1;  //Cursor position index for buttons 1-3
    int getInput();     //Input loop function
};

#endif