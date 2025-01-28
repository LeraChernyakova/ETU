#pragma once

#include "Cell.h"
#include "FieldScheme.h"
#include <typeinfo>
#include <unordered_map>
#include <algorithm>

class CellRegister {
public:
    static char getSymb(const Cell& cell);
    static CellType getCellType(const Cell& cell);
    static char getSymb(CellType cell);
    static CellType getType(char symb);
private:
    static std::unordered_map<std::size_t, CellType> map;
    static std::unordered_map<CellType, char> cell_map;
};