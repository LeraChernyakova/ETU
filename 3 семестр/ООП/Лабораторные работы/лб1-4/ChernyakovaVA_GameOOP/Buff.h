#pragma once

#include "PlayerEvents.h"
#include "RNGenerator.h"

class Buff : public PlayerEvents {
private:
    int power_up;
public:
    explicit Buff(Player* pl, int value);
    void execute() final;
    ~Buff() override = default;
};