#pragma once

#include "FieldScheme.h"
#include "Concepts.h"

template<int Cx, int Cy, int Xr, int Yr, TCellChanger CellChanger>
class EllipseGenerator {
public:
    void operator()(FieldScheme& scheme) {
        int twoASq = 2 * Xr * Xr;
        int twoBSq = 2 * Yr * Yr;
        int x = Xr;
        int y = 0;
        int xCh = Yr * Yr * (1 - 2 * Xr);
        int yCh = Xr * Xr;
        int err = 0;
        int stopX = twoBSq * Xr;
        int stopY = 0;

        while (stopX >= stopY) {
            addPoints(scheme, Cx, Cy, x, y);
            ++y;
            stopY += twoASq;
            err += yCh;
            yCh += twoASq;
            if ((2 * err + xCh) > 0) {
                --x;
                stopX -= twoBSq;
                err += xCh;
                xCh += twoBSq;
            }
        }

        x = 0;
        y = Yr;
        xCh = Yr * Yr;
        yCh = Xr * Xr * (1 - 2 * Yr);
        err = 0;
        stopX = 0;
        stopY = twoASq * Yr;
        while (stopX <= stopY) {
            addPoints(scheme, Cx, Cy, x, y);
            ++x;
            stopX += twoBSq;
            err += xCh;
            xCh += twoBSq;
            if ((2 * err + yCh) > 0) {
                --y;
                stopY -= twoASq;
                err += yCh;
                yCh += twoASq;
            }
        }
    }

private:
    CellChanger cell_changer;
    void addPoints(FieldScheme& scheme, int cx, int cy, int x, int y) {
        cell_changer(scheme.array[Cy + y][Cx + x]);
        cell_changer(scheme.array[Cy + y][Cx - x]);
        cell_changer(scheme.array[Cy - y][Cx + x]);
        cell_changer(scheme.array[Cy - y][Cx - x]);
    }

};

template<int Cx, int Cy, int R, TCellChanger T>
class CircleGenerator :public EllipseGenerator<Cx, Cy, R, R, T> {};