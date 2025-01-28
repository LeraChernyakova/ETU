#pragma once
#include "Advantages.h"
#include "../Objects/Player.h"
#include "../Advantages/Exit.h"

class Money: public Advantages {
    public:
        void occasion(Player& player) final;
        void react(Player& player, Union union1) final;
};
