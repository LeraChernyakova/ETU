#pragma once
//#ifndef OOP_LAB1_PRINTFIELD_H
//#define OOP_LAB1_PRINTFIELD_H
#include "../Objects/Field.h"
#include "PrintCell.h"
#include <windows.h>

class PrintField{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
public:
    void print(Field& field);

    PrintField();
    void setcursor(bool visible, DWORD size);
    void gotoxy(int x, int y);
    void printLine(int width);
};

//#endif //OOP_LAB1_PRINTFIELD_H
