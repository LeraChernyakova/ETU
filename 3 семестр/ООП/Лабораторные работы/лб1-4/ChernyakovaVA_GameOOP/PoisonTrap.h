#pragma once

#include "PlayerEvents.h"

class PoisonTrap : public PlayerEvents {
private:
    int dmg;
public:
    explicit PoisonTrap(Player* pl, int damage);
    void execute() final;
    ~PoisonTrap() override = default;
};