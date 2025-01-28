#pragma once

#include "IEvent.h"
#include "FactoryEvent.h"

class Cell {
private:
    bool active;
    bool barrier;
    IEvent* event;
public:
    Cell(bool active, bool barrier);
    Cell() = default;
    ~Cell();

    void setActive();
    bool getActive();

    void setBarrier();
    bool getBarrier();

    IEvent* getEvent();
    void setEvent(IEvent* create_event);
    void deleteEvent();
};
