#pragma once
#include "Advantages.h"
#include "../Objects/Player.h"

class Peaceful: public Advantages {
public:
    void react(Player& player, Union union1) final;
    void occasion(Player& player) final;
};
