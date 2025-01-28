#include "Cell.h"

//#include "IEvent.h"

Cell::Cell(bool patency, IEvent* fact) {
    this->patency = patency;
    this->fact = fact;
}
Cell::Cell() {
    patency = true;
    fact = nullptr;
    active = false;
}

IEvent* Cell::getFact() const {
    return fact;
}
void Cell::setPatency(bool value) {
    this->patency = value;
}
bool Cell::getPatency() const {
    return patency;
}
void Cell::react() const {
    if (!fact)
        return;
    fact->event();
    if (!fact->isActive()) {
        delete fact;
        fact = nullptr;
    }
}
void Cell::changeFact(IEvent* new_fact) {
    if (fact == nullptr) {
        fact = new_fact;
    }
    else {
        delete fact;
        fact = new_fact;
    }
}

Cell::Cell(const Cell& obj) noexcept {
    this->patency = obj.patency;
    this->fact = obj.fact->clone();
}

Cell& Cell::operator=(const Cell& obj) noexcept {
    if (this == &obj) {
        return *this;
    }
    delete fact;
    this->fact = obj.fact->clone();
    this->patency = obj.patency;
    return *this;
}
Cell::Cell(Cell&& obj) noexcept {
    this->patency = obj.patency;
    this->fact = obj.fact;
    obj.fact = nullptr;
    obj.patency = false;
}
Cell& Cell::operator=(Cell&& obj) noexcept {
    if (this == &obj) {
        return *this;
    }
    delete fact;
    this->patency = obj.patency;
    this->fact = obj.fact;
    obj.fact = nullptr;
    obj.patency = false;
    return *this;
}
Cell::~Cell() {
    delete fact;
}
bool Cell::getActive() const {
    return active;
}
void Cell::setActive(bool value) {
    active = value;
}