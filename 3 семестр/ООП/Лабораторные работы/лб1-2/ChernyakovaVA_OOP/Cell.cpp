#include "Cell.h"


Cell::Cell(bool active, bool barrier) : active(active), barrier(barrier) {
    event = nullptr;
}

void Cell::setActive() {
    this->active ? this->active = false : this->active = true;
}

bool Cell::getActive() {
    return this->active;
}

void Cell::setBarrier() {
    this->barrier = true;
}

bool Cell::getBarrier() {
    return this->barrier;
}

IEvent* Cell::getEvent() {
    return this->event;
}

void Cell::setEvent(IEvent* create_event) {
    this->event = create_event;
}

void Cell::deleteEvent() {
    event = nullptr;
}

Cell::~Cell() {
    if (!event)
        delete event;
}
