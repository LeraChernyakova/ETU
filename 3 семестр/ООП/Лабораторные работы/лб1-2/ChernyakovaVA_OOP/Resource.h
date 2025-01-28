#pragma once
#include "GoodEvent.h"

class Resource :public GoodEvent {
public:
    void addGood(Player& player) final;
    void reaction(Player& player) final;
};