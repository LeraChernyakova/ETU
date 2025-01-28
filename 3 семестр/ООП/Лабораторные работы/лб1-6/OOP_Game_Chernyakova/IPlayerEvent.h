#pragma once

#include "IEvent.h"
#include "Player.h"

class IPlayerEvent : public IEvent {
public:
    explicit IPlayerEvent(Player* player);
    void event() override = 0;
    IEvent* clone() override = 0;
    bool isActive() override = 0;
protected:
    Player* player;
};