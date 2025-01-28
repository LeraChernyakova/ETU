#pragma once

#include "FieldScheme.h"
#include "Concepts.h"

template<int X, int Y, TCellChanger CellChanger>
class PointGenerator {
public:
    void operator()(FieldScheme& scheme) {
        if (Y >= 0 && X >= 0 && Y < scheme.height && X < scheme.width)
            cell_changer(scheme.array[Y][X]);
    }
private:
    CellChanger cell_changer;
};