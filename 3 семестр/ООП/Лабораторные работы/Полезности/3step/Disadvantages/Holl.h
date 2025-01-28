#pragma once
#include "Disadvantages.h"
#include "../Objects/Player.h"

class Holl: public Disadvantages {
    public:
        void damage(Player& player) final;
        void react(Player& player, Union union1) final;
};
