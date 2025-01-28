#include "Field.h"
#include <iostream>

using namespace std;
Field::Field() : Field(15, 15) {}

Field::Field(int width, int height) : observer(nullptr) {
    if (width <= 0)
        width = 15;
    if (height <= 0)
        height = 15;
    this->width = width;
    this->height = height;

    this->array = new Cell * [this->height]();
    for (int i = 0; i < this->height; i++) {
        this->array[i] = new Cell[this->width]();
    }

}

Field::Field(const Field& obj) noexcept {
    this->height = obj.height;
    this->width = obj.width;

    this->array = new Cell * [this->height];
    for (int i = 0; i < this->height; i++) {
        this->array[i] = new Cell[this->width];
        for (int j = 0; j < this->width; j++) {
            this->array[i][j] = obj.array[i][j];
        }
    }
}

Field::Field(Field&& obj) noexcept {
    this->height = obj.height;
    this->width = obj.width;
    this->array = obj.array;
    obj.height = obj.width = 0;
    obj.array = nullptr;

}

Field& Field::operator=(const Field& obj) noexcept {
    if (this == &obj) {
        return *this;
    }
    for (unsigned int i = 0; i < this->height; i++) {
        delete[] this->array[i];
    }
    delete[] this->array;
    this->height = obj.height;
    this->width = obj.width;
    this->array = new Cell * [this->height];
    for (unsigned int i = 0; i < this->height; i++) {
        this->array[i] = new Cell[this->width];
        for (unsigned int j = 0; j < this->width; j++) {
            this->array[i][j] = obj.array[i][j];
        }
    }
    return *this;
}
Field& Field::operator=(Field&& obj) noexcept {
    if (this == &obj) {
        return *this;
    }
    for (unsigned int i = 0; i < this->height; i++) {
        delete[] this->array[i];
    }
    delete[] this->array;
    this->height = obj.height;
    this->width = obj.width;
    this->array = obj.array;
    obj.height = obj.width = 0;
    obj.array = nullptr;
    return *this;
}

Field::~Field() {
    for (int i = 0; i < this->height; i++) {
        delete[] this->array[i];
    }
    delete[] this->array;
}

int Field::getWidth() const {
    return this->width;
}
int Field::getHeight() const {
    return this->height;
}

bool Field::isPointPassable(int x, int y) {
    return x >= 0 && y >= 0 && x < width&& y < height&& array[y][x].getPatency();
}

const Cell& Field::getCell(int x, int y) {
    return array[y][x];

}
void Field::setCellPatency(int x, int y, bool value) {
    array[y][x].setPatency(value);
    if (observer)
        observer->onCellPatencyChanged(x, y, value);
}
void Field::setCellEvent(int x, int y, IEvent* event) {
    array[y][x].changeFact(event);
    if (observer)
        observer->onCellEventChanged(x, y);
}
IEvent* Field::getCellEvent(int x, int y) {
    return array[y][x].getFact();
}
void Field::setObserver(IFieldObserver* obs) {
    observer = obs;
}
void Field::setCellActive(int x, int y, bool value) {
    array[y][x].setActive(value);
    if (observer) {
        observer->onCellActivityChanged(x, y, array[y][x]);
    }
}
const Cell* Field::operator[](int row) const {
    return array[row];
}
Field::Field(int width, int height, Cell** array) {
    this->width = width;
    this->height = height;
    this->array = array;
    observer = nullptr;
}