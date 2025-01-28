#pragma once
#include "Disadvantages.h"

class Defeat: public Disadvantages {
public:
    void damage(Player& player) final;
    void react(Player& player, Union union1) final;
};

