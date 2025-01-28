#pragma once
#include "IEvent.h"

class BadEvent : public IEvent {
public:
    virtual void addBad(Player& player) = 0;
    void cutPlayerScore(Player& player);
};