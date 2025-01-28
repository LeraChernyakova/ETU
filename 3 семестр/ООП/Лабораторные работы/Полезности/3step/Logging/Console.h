#pragma once
#include "Output.h"
#include "../Control/WinConsoleControl.h"
#include <iostream>

class Console: public Output {
    int x, y;
    WinConsoleControl cons;
public:
    explicit Console(int y);
    Output& operator<<(std::string message) final;
    void changeY(int a);
};

