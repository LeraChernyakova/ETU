#pragma once

#include "Cell.h"
#include "Clan.h"
#include "Hungry.h"
#include "Cave.h"
#include "Exit.h"
#include "Resource.h"
#include <iostream>

class CellView {
public:
    CellView() = default;

    void printCell(Cell cell);
};