#pragma once
#include "FactoryEvent.h"
#include "Resource.h"

class FactoryResource : public FactoryEvent {
public:
    IEvent* createEvent() final;
};
