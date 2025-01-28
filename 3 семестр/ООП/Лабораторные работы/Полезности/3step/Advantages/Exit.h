#pragma once
#include "Advantages.h"

class Exit: public Advantages {
public:
    void react(Player& player, Union union1) final;
    void occasion(Player& player) final;
};

