#pragma once
#include "FactoryEvent.h"
#include "Exit.h"

class FactoryExit : public FactoryEvent {
public:
    IEvent* createEvent() final;
};
