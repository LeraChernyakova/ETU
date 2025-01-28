#pragma once
#include "../Control/Event.h"
#include "../Factory/Factory.h"

class Advantages: public Event {
public:
    virtual void occasion(Player& player)=0;
    void buff(Player& player);
};

