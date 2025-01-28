#pragma once
#include "FactoryEvent.h"
#include "Cave.h"

class FactoryCave : public FactoryEvent {
public:
    IEvent* createEvent() final;
};
