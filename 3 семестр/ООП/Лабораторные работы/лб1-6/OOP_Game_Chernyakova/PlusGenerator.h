#pragma once

#include "FieldScheme.h"
#include "Concepts.h"

template<TCellChanger CellChanger>
class PlusGenerator {
public:
    void operator()(FieldScheme& scheme) {
        int x = scheme.width / 2;
        int y = scheme.height / 2;
        for (int i = 0; i < scheme.height; ++i) {
            cell_changer(scheme.array[i][x]);
        }
        for (int i = 0; i < scheme.width; ++i) {
            cell_changer(scheme.array[y][i]);
        }
    }
private:
    CellChanger cell_changer;

};