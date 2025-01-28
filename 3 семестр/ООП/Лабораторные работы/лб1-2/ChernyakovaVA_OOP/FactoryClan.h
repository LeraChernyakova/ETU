#pragma once
#include "FactoryEvent.h"
#include "Clan.h"

class FactoryClan : public FactoryEvent {
public:
    IEvent* createEvent() final;
};
