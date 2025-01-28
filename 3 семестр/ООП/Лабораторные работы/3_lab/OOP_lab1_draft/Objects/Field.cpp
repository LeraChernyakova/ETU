#include <fstream>
#include "Field.h"


Field::Field(int height, int width) : height(height), width(width) {
    srand(static_cast<unsigned int>(time(nullptr)));
    array = new Cell *[height];
    for (int i = 0; i < height; i++) {
        array[i] = new Cell[width];
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1) {
                array[i][j] = Cell(i, j, false, !(rand() % 6));
            } else
                array[i][j] = Cell(i, j, false, false);
        }
    }
    array[0][0].activeReaction();
    x_active = 0;
    y_active = 0;
    field_observer = nullptr;
}

Field::Field() : Field(10, 10) {}

void Field::setEventOnCell(Factory *factory) {
    int count = 0;
    while (count < 2) {
        int y = rand() % (height - 1);
        int x = rand() % (width - 1);
        if (!array[y][x].getBarrier() && !array[y][x].getEvent() && !(x == 0 && y == 0)) {
            array[y][x].changeEvent(factory->createEvent());
            count++;
        }
    }
}

void Field::setFieldEvents() {

    Factory *enemy_factory = new EnemyFactory();
    Field::setEventOnCell(enemy_factory);
    delete enemy_factory;

    Factory *trap_factory = new TrapFactory();
    Field::setEventOnCell(trap_factory);
    delete trap_factory;

    Factory *money_factory = new MoneyFactory();
    Field::setEventOnCell(money_factory);
    delete money_factory;

    Factory *food_factory = new FoodFactory();
    Field::setEventOnCell(food_factory);
    delete food_factory;
}

Field::Field(const Field &field) {
    height = field.height;
    width = field.width;
    x_active = field.x_active;
    y_active = field.y_active;
    field_observer = field.field_observer;
    array = new Cell *[height];
    for (int i = 0; i < field.height; i++) {
        array[i] = new Cell[width];
    }
    for (int i = 0; i < field.height; i++) {
        for (int j = 0; j < field.width; j++) {
            array[i][j] = field.array[i][j];
        }
    }
}

Field::Field(Field &&field) noexcept {
    std::swap(height, field.height);
    std::swap(width, field.width);
    std::swap(x_active, field.x_active);
    std::swap(y_active, field.y_active);
    std::swap(field_observer, field.field_observer);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::swap(array[i][j], field.array[i][j]);
        }
    }
}


Field &Field::operator=(const Field &field) {
    if (this != &field) {
        for (int i = 0; i < height; i++) {
            delete array[i];
        }
        delete[] array;
        height = field.height;
        width = field.width;
        x_active = field.x_active;
        y_active = field.y_active;
        field_observer = field.field_observer;
        array = new Cell *[height];
        for (int i = 0; i < field.height; i++) {
            array[i] = new Cell[width];
        }
        for (int i = 0; i < field.height; i++) {
            for (int j = 0; j < field.width; j++) {
                array[i][j] = field.array[i][j];
            }
        }
    }
    return *this;
}

Field::~Field() {
    for (int i = 0; i < height; i++) {
        delete array[i];
    }
    delete[] array;
    delete field_observer;
}

int Field::getHeight() const {
    return this->height;
}

int Field::getWidth() const {
    return this->width;
}

Cell Field::getCell(int y, int x) {
    return array[y][x];
}

int Field::getActiveCellX() const {
    return x_active;
}

int Field::getActiveCellY() const {
    return y_active;
}

void Field::setExit(Log &log) {
    Factory *exit_factory = new ExitFactory();
    array[height - 1][width - 1].changeEvent(exit_factory->createEvent());
    field_observer->openExit();
    delete exit_factory;
}

void Field::moveUp(int step, Player &player, Log &log) {
    array[y_active][x_active].activeReaction();
    array[y_active][x_active].setGood();
    y_active = (height + y_active - step) % height;
    field_observer->changedPlayerPosition(x_active, y_active);
    array[y_active][x_active].activeReaction();
    if (array[y_active][x_active].getEvent())
        array[y_active][x_active].getEvent()->playerReact(player, log);
    if (player.getOpenExit() && !array[height - 1][width - 1].getEvent())
        Field::setExit(log);
}

void Field::moveDown(int step, Player &player, Log &log) {
    array[y_active][x_active].activeReaction();
    array[y_active][x_active].setGood();
    y_active = (height + y_active + step) % height;
    field_observer->changedPlayerPosition(x_active, y_active);
    array[y_active][x_active].activeReaction();
    if (array[y_active][x_active].getEvent())
        array[y_active][x_active].getEvent()->playerReact(player, log);
    if (player.getOpenExit() && !array[height - 1][width - 1].getEvent())
        Field::setExit(log);
}

void Field::moveRight(int step, Player &player, Log &log) {
    array[y_active][x_active].activeReaction();
    array[y_active][x_active].setGood();
    x_active = (width + x_active + step) % width;
    field_observer->changedPlayerPosition(x_active, y_active);
    array[y_active][x_active].activeReaction();
    if (array[y_active][x_active].getEvent())
        array[y_active][x_active].getEvent()->playerReact(player, log);
    if (player.getOpenExit() && !array[height - 1][width - 1].getEvent())
        Field::setExit(log);
}

void Field::moveLeft(int step, Player &player, Log &log) {
    array[y_active][x_active].activeReaction();
    array[y_active][x_active].setGood();
    x_active = (width + x_active - step) % width;
    field_observer->changedPlayerPosition(x_active, y_active);
    array[y_active][x_active].activeReaction();
    if (array[y_active][x_active].getEvent())
        array[y_active][x_active].getEvent()->playerReact(player, log);
    if (player.getOpenExit() && !array[height - 1][width - 1].getEvent())
        Field::setExit(log);
}

IFieldObserver *&Field::getFieldObserver() {
    return field_observer;
}

void Field::setObserver(Log &log) {
    field_observer = new FieldObserver(log);
}

