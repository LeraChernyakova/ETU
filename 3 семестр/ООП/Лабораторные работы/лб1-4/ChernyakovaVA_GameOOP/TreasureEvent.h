#pragma once

#include "PlayerEvents.h"

class TreasureEvent : public PlayerEvents {
public:
    explicit TreasureEvent(Player* pl);
    void execute() override;
    ~TreasureEvent() override = default;
};