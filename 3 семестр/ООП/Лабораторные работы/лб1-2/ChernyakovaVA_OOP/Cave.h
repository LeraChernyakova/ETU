#pragma once

#include "GoodEvent.h"

class Cave : public GoodEvent {
public:
    void reaction(Player& player) final;
    void addGood(Player& player) final;
};
