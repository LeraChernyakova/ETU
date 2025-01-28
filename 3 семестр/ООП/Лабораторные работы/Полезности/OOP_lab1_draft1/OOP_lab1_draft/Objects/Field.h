
#ifndef OOP_LAB1_FIELD_H
#define OOP_LAB1_FIELD_H

#include "Cell.h"
#include "../Factory/FoodFactory.h"
#include "../Factory/ExitFactory.h"
#include "Player.h"
#include "../Factory/Factory.h"
#include "../Factory/EnemyFactory.h"
#include "../Factory/TrapFactory.h"
#include "../Factory/MoneyFactory.h"
#include "../Log/Observers/FieldObserver.h"
#include <ctime>
#include <iostream>


class Field {
private:
    int height, width;
    Cell **array;
    int x_active, y_active;
    IFieldObserver *field_observer;
public:
    Field(int height, int width);
    Field();
    Field(const Field &field);
    Field(Field &&field) noexcept ;
    Field &operator=(const Field &field);
    ~Field();
    int getHeight() const;
    int getWidth() const;
    Cell getCell(int x, int y);
    int getActiveCellX() const;
    int getActiveCellY() const;
    IFieldObserver *&getFieldObserver();
    void moveUp(int step, Player &player, Log &log);
    void moveDown(int step, Player &player, Log &log);
    void moveRight(int step, Player &player, Log &log);
    void moveLeft(int step, Player &player, Log &log);
    void setExit(Log &log);
    void setFieldEvents();
    void setEventOnCell(Factory *factory);
};

#endif //OOP_LAB1_FIELD_H
