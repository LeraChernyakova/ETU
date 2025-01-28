#pragma once

#include "PlayerEvents.h"

class HealEvent : public PlayerEvents {
public:
    explicit HealEvent(Player* pl);
    void execute() final;
    ~HealEvent() override = default;
};