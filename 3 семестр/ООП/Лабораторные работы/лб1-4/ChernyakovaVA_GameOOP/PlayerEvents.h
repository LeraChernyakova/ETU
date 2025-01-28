#pragma once

#include "Event.h"
#include "Player.h"

class PlayerEvents : public Event {
protected:
    Player* player;
public:
    void execute() override = 0;
    virtual ~PlayerEvents() = default;
};