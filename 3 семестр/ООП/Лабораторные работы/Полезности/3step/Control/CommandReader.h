#pragma once
#include <conio.h>
#include <ctime>
#include "../Control/Mediator.h"
#include "../Logging/Union.h"

class CommandReader {
public:
    void makeField(int& x_size, int& y_size, Union union1);
    void gameStart(GameField field, Mediator med, Union union1, Instruments instr, Player player, Factory* factory, WinConsoleControl cons);
    void readMesInfo(bool *info1);
    void deleteShit(Union union1, Factory* factory);
};

