#pragma once

#include "Field.h"
#include "CellView.h"
#include <windows.h>

class FieldView{
private:
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
public:
    FieldView() = default;
    
    void printLine(int width);
    void printField(Field& field);
};


