#pragma once

#include "Field.h"
#include "FieldView.h"
#include "CommandReader.h"

class Controller {
public:
    int getFieldHeight(CommandReader& reader);
    int getFieldWidth(CommandReader& reader);

    void movePlayerUp(Field& field, Player& player);
    void movePlayerDown(Field& field, Player& player);
    void movePlayerRight(Field& field, Player& player);
    void movePlayerLeft(Field& field, Player& player);

    void getAction(bool& game, Player& player, Field& field, CommandReader& reader);

    void printPlayerInfo(Player& player);

};

