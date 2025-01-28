#pragma once

#include "FieldScheme.h"
#include "Concepts.h"

template<int X0, int Y0, int X1, int Y1, TCellChanger CellChanger>
class LineGenerator {
public:
    void operator()(FieldScheme& scheme) {
        int dx = X1 - X0;
        int dy = Y1 - Y0;
        int adx = abs(dx);
        int ady = abs(dy);
        int err = 0;
        int sx = dx > 0 ? 1 : -1;
        int sy = dy > 0 ? 1 : -1;
        if (adx > ady) {
            for (int x = X0, y = Y0; sx < 0 ? x >= X1 : x <= X1; x += sx) {
                cell_changer(scheme.array[y][x]);
                err += ady;
                if (err << 1 >= adx) {
                    y += sy;
                    err -= adx;
                }
            }
        }
        else {
            for (int x = X0, y = Y0; sy < 0 ? y >= Y1 : y <= Y1; y += sy) {
                cell_changer(scheme.array[y][x]);
                err += adx;
                if (err << 1 >= ady) {
                    x += sx;
                    err -= ady;
                }
            }
        }
    }

private:
    CellChanger cell_changer;
};