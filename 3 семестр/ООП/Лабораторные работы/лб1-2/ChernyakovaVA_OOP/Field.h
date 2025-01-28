#pragma once

#include "Cell.h"
#include "Player.h"
#include "FactoryEvent.h"
#include "FactoryCave.h"
#include "FactoryClan.h"
#include "FactoryExit.h"
#include "FactoryHungry.h"
#include "FactoryResource.h"

#include <ctime>
#include <iostream>

class Field {
private:
    int height;
    int width;
    int cell_x;
    int cell_y;
    Cell** cells;
public:
    Field(int height, int width);
    Field();
    Field(const Field& field);
    Field(Field&& field) noexcept;
    Field& operator=(const Field& field);
    ~Field();

    int getHeight() const;
    int getWidth() const;
    Cell getCell(int x, int y);
    int getCellX() const;
    int getCellY() const;

    void moveUp(int step, Player& player);
    void moveDown(int step, Player& player);
    void moveRight(int step, Player& player);
    void moveLeft(int step, Player& player);

    void setEventOnCell(FactoryEvent* factory);
    void setFieldEvents();
    void setExit(Player& player);
};

