#pragma once
#include "Disadvantages.h"
#include "../Objects/Player.h"

class Enemy: public Disadvantages {
public:
    void react(Player& player, Union union1) final;
    void damage(Player& player) final;
};

