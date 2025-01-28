#pragma once
#include "../Objects/GameField.h"
#include "WinConsoleControl.h"

class Instruments {
        Factory* factory1;
public:

        void drawField(int x_start, int y_start, GameField& field, WinConsoleControl cons);

        void drawEvents(GameField& field, Factory* factory);

        void showBill(Player& player, GameField field, WinConsoleControl cons);

        void changePlayer(int x, int y, Instruments inst, GameField& field, char object, WinConsoleControl cons);

        void changePosition(GameField field, WinConsoleControl cons);
};