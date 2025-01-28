#pragma once
#include "PoisonTrap.h"
#include "FrozenTrap.h"
#include "Buff.h"
#include "CoinEvent.h"
#include "HealEvent.h"
#include "FieldNoWalls.h"
#include "IEventGen.h"

class PlayerEventGen : public IEventGen {
public:
    explicit PlayerEventGen(Field* pField) { field = pField; };
    Event* generate() final;
    ~PlayerEventGen() override = default;
};