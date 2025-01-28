#pragma once
#include "../Objects/Player.h"
#include "../Logging/Union.h"

class Event {
public:
    virtual void react(Player& player, Union union1)=0;
    virtual ~Event() {};
};



