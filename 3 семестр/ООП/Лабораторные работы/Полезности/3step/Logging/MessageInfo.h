#pragma once
#include "Output.h"
#include "FileObject.h"
#include "Console.h"
#include <iostream>

class MessageInfo {
    bool levels[3];
    bool console;
    bool file;
    Output* fileOut= nullptr;
    Output* consoleOut= nullptr;
public:
    explicit MessageInfo(bool level1=false, bool level2=false, bool level3=false, bool file=false, bool console=false, int y=0);
    bool getLevel(int number);
    Output* getConsole();
    Output* getFile();
    bool getConsoleT();
    bool getFileT();
};

