#include "Cell.h"


Cell::Cell(int x, int y, bool active, bool barrier) : x(x), y(y), active(active), barrier(barrier) {
    event = nullptr;
}

Cell::Cell(int x, int y) : Cell(x, y, false, false) {
}

Cell::Cell() = default;

void Cell::activeReaction() {
    this->active ? this->active = false : this->active = true;
}

int Cell::getX() {
    return this->x;
}

int Cell::getY() {
    return this->y;
}

bool Cell::getActive() {
    return this->active;
}

void Cell::changeBarrier() {
    this->barrier = true;
}

bool Cell::getBarrier() {
    return this->barrier;
}

Event *Cell::getEvent() {
    return this->event;
}

void Cell::changeEvent(Event *new_event) {
    this->event = new_event;
}

void Cell::setGood() {
    event = nullptr;
}

Cell::~Cell() {
    if (!event)
        delete event;
}
