#pragma once
#include "IEvent.h"

class FactoryEvent {
public:
    virtual IEvent* createEvent() = 0;
    virtual ~FactoryEvent() { };
};