#pragma once
#include "BadEvent.h"

class Clan : public BadEvent {
public:
    void reaction(Player& player) final;
    void addBad(Player& player) final;
};