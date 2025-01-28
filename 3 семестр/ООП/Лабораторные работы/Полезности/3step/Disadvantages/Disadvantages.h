#pragma once
#include "../Control/Event.h"

class Disadvantages: public Event {
    virtual void damage(Player& player)=0;
    void debuff(Player& player);
};


