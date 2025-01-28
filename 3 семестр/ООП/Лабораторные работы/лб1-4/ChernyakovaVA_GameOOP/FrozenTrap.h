#pragma once

#include "PlayerEvents.h"

class FrozenTrap : public PlayerEvents {
private:
    int decrease;
public:
    explicit FrozenTrap(Player* pl, int dec);
    void execute() final;
    ~FrozenTrap() override = default;
};