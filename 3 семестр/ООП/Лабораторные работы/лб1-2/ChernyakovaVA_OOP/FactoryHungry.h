#pragma once
#include "FactoryEvent.h"
#include "Hungry.h"

class FactoryHungry : public FactoryEvent {
public:
    IEvent* createEvent() final;
};

