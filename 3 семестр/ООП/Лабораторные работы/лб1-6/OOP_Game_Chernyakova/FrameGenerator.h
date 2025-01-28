#pragma once

#include "FieldScheme.h"
#include "Concepts.h"
template<int X, int Y, int Thickness, TCellChanger CellChanger>
class FrameGenerator {
public:
    void operator()(FieldScheme& scheme) {
        for (int i = Y; i <= scheme.height - Y; ++i) {
            for (int j = X; j <= scheme.width - X; ++j) {
                if ((i < Thickness + Y || i > scheme.height - Thickness - 1 - Y)
                    && (j < Thickness + X || j > scheme.width - Thickness - 1 - X)) {
                    cell_changer(scheme.array[i][j]);
                }
            }
        }
    }
private:
    CellChanger cell_changer;
};