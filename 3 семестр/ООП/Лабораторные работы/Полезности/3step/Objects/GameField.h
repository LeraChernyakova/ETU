#pragma once
#include "Cell.h"
#include "../Logging/Union.h"

class GameField {
        int player_x=0, player_y=0;
        int size_x;// field size
        int size_y;
        Cell** field_of_cells;
    public:

        GameField();
        explicit GameField(int size_x, int size_y);

        ~GameField();

        GameField(const GameField & field);
        GameField &operator=(const GameField &field);

        GameField(GameField&& field) noexcept;
        GameField &operator=(GameField&& field) noexcept;

        int getPlayerX();
        int getPlayerY();
        int getSizeY();
        int getSizeX();
        Cell** getField();

        void changeData(int x_change, int y_change);

        void doOccasions(Player& player, Union union1);
};


