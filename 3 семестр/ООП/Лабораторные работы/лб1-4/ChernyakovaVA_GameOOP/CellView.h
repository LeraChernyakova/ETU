#pragma once

#include "Cell.h"
#include "CoinEvent.h"
#include "HealEvent.h"
#include "Buff.h"
#include "PoisonTrap.h"
#include "FrozenTrap.h"
#include "FieldNoWalls.h"
#include "TreasureEvent.h"

class CellView {
private:
    char cell_view;
public:
    explicit CellView(Cell& cell);
    ~CellView() = default;
    char get_view() const;
};