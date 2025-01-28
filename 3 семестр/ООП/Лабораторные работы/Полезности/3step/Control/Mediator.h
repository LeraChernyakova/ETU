#pragma once
#include "../Objects/GameField.h"
#include "Instruments.h"
#include "../Factory/DefeatFactory.h"
#include "../Logging/Union.h"

class Mediator {
public:
        void checkHole(Player& player, GameField& field, Instruments inst, Union union1, WinConsoleControl cons);
        void checkBill(Player& player, GameField& field, Factory* factory, Instruments inst, Union union1, WinConsoleControl cons);
        void checkHP(Player& player, GameField& field, char& lp, Union union1, WinConsoleControl cons);
        void checkParameters(Player& player, GameField& field,  Factory* factory, char& lp, Instruments inst, Union union1, WinConsoleControl cons);

        void move(int x_change, int y_change, GameField& field, Player& player, char& lp, Factory* factory, Instruments inst, Union union1, WinConsoleControl cons);

};

