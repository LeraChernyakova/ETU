#pragma once

#include <windows.h>
#include "Field.h"

class PrintField {
public:
    PrintField();
    void printField(const Field& field);
    void reprintCell(int x, int y, const Cell& cell);
    static void setCursorposition(int x, int y);

private:
    HANDLE handle;

};