#pragma once
#include "IEvent.h"

class GoodEvent : public IEvent {
public:
    virtual void addGood(Player& player) = 0;
    void addPlayerScore(Player& player);
};
