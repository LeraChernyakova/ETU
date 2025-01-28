#pragma once

#include "PlayerEvents.h"
#include "RNGenerator.h"

class CoinEvent : public PlayerEvents {
private:
    int coins;
public:
    CoinEvent(Player* pl, int coin);
    void execute();
    ~CoinEvent() override = default;
};