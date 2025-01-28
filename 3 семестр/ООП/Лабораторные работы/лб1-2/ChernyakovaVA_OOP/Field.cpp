#include <fstream>
#include "Field.h"

Field::Field(int height, int width) : height(height), width(width) {
    srand(static_cast<unsigned int>(time(nullptr)));
    cells = new Cell * [height];
    for (int i = 0; i < height; i++)
        cells[i] = new Cell[width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i != 0 and i != height - 1 and j != 0 and j != width - 1) {//непроходимые клетки не устанавливаются по краям поля, чтобы игрок мог гарантированно дойти до выхода
                cells[i][j] = Cell(false, !(rand() % 6));
            }
            else
                cells[i][j] = Cell(false, false);
        }
    }
    cells[0][0].setActive();
    cell_x = 0;
    cell_y = 0;
}

Field::Field() : Field(10, 10) {}

Field::Field(const Field& field) {
    height = field.height;
    width = field.width;
    cell_x = field.cell_x;
    cell_y = field.cell_y;
    cells = new Cell * [height];
    for (int i = 0; i < field.height; i++) {
        cells[i] = new Cell[width];
    }
    for (int i = 0; i < field.height; i++) {
        for (int j = 0; j < field.width; j++) {
            cells[i][j] = field.cells[i][j];
        }
    }
}

Field::Field(Field&& field) noexcept {
    std::swap(height, field.height);
    std::swap(width, field.width);
    std::swap(cell_x, field.cell_x);
    std::swap(cell_y, field.cell_y);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::swap(cells[i][j], field.cells[i][j]);
        }
    }
}

Field& Field::operator=(const Field& field) {
    if (this != &field) {
        for (int i = 0; i < height; i++) {
            delete cells[i];
        }
        delete[] cells;
        height = field.height;
        width = field.width;
        cell_x = field.cell_x;
        cell_y = field.cell_y;
        cells = new Cell * [height];
        for (int i = 0; i < field.height; i++) {
            cells[i] = new Cell[width];
        }
        for (int i = 0; i < field.height; i++) {
            for (int j = 0; j < field.width; j++) {
                cells[i][j] = field.cells[i][j];
            }
        }
    }
    return *this;
}

Field::~Field() {
    for (int i = 0; i < height; i++) 
        delete[] cells[i];
    delete[] cells;
}

int Field::getHeight() const {
    return this->height;
}

int Field::getWidth() const {
    return this->width;
}

Cell Field::getCell(int y, int x) {
    return cells[y][x];
}

int Field::getCellX() const {
    return cell_x;
}

int Field::getCellY() const {
    return cell_y;
}

void Field::moveUp(int step, Player& player) {
    cells[cell_y][cell_x].setActive();
    cells[cell_y][cell_x].deleteEvent();
    cell_y = (height + cell_y - step) % height;//зацикливание поля
    cells[cell_y][cell_x].setActive();
    if (cells[cell_y][cell_x].getEvent())
        cells[cell_y][cell_x].getEvent()->reaction(player);
    if (player.getOpenExit() and !cells[height - 1][width - 1].getEvent())
        Field::setExit(player);
}

void Field::moveDown(int step, Player& player) {
    cells[cell_y][cell_x].setActive();
    cells[cell_y][cell_x].deleteEvent();
    cell_y = (height + cell_y + step) % height;
    cells[cell_y][cell_x].setActive();
    if (cells[cell_y][cell_x].getEvent())
        cells[cell_y][cell_x].getEvent()->reaction(player);
    if (player.getOpenExit() and !cells[height - 1][width - 1].getEvent())
        Field::setExit(player);
}

void Field::moveRight(int step, Player& player) {
    cells[cell_y][cell_x].setActive();
    cells[cell_y][cell_x].deleteEvent();
    cell_x = (width + cell_x + step) % width;
    cells[cell_y][cell_x].setActive();
    if (cells[cell_y][cell_x].getEvent())
        cells[cell_y][cell_x].getEvent()->reaction(player);
    if (player.getOpenExit() and !cells[height - 1][width - 1].getEvent())
        Field::setExit(player);
}

void Field::moveLeft(int step, Player& player) {
    cells[cell_y][cell_x].setActive();
    cells[cell_y][cell_x].deleteEvent();
    cell_x = (width + cell_x - step) % width;
    cells[cell_y][cell_x].setActive();
    if (cells[cell_y][cell_x].getEvent())
        cells[cell_y][cell_x].getEvent()->reaction(player);
    if (player.getOpenExit() and !cells[height - 1][width - 1].getEvent())
        Field::setExit(player);
}

void Field::setEventOnCell(FactoryEvent* factory) {
    int count = 0;
    while (count < 3) {
        int y = rand() % (height - 1);
        int x = rand() % (width - 1);
        if (!cells[y][x].getBarrier() and !cells[y][x].getEvent() and !(x == 0 and y == 0)) {
            cells[y][x].setEvent(factory->createEvent());
            count++;
        }
    }
}

void Field::setFieldEvents() {
    FactoryEvent *factory_cave = new FactoryCave();
    Field::setEventOnCell(factory_cave);
    delete factory_cave;

    FactoryEvent *factory_clan = new FactoryClan();
    Field::setEventOnCell(factory_clan);
    delete factory_clan;

    FactoryEvent *factory_hungry = new FactoryHungry();
    Field::setEventOnCell(factory_hungry);
    delete factory_hungry;

    FactoryEvent *factory_resource = new FactoryResource();
    Field::setEventOnCell(factory_resource);
    delete factory_resource;
}

void Field::setExit(Player& player) {
    FactoryEvent *factory_exit = new FactoryExit();
    cells[height - 1][width - 1].setEvent(factory_exit->createEvent());
    delete factory_exit;
}




