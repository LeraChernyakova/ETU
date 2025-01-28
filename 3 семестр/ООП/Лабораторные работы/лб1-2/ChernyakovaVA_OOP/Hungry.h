#pragma once
#include "BadEvent.h"

class Hungry : public BadEvent {
public:
    void reaction(Player& player) final;
    void addBad(Player& player) final;
};