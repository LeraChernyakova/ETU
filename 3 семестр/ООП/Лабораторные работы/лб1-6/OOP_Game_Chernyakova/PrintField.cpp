#include <iostream>
#include "PrintField.h"
#include "CellRegister.h"

PrintField::PrintField() {
    CONSOLE_CURSOR_INFO info{ 10, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void PrintField::printField(const Field& field) {
    setCursorposition(0, 0);
    for (int i = 0; i < field.getHeight(); ++i) {
        auto row = field[i];
        for (int j = 0; j < field.getWidth(); ++j) {
            char s = CellRegister::getSymb(row[j]);
            std::cout << s;
        }
        std::cout << "\n";
    }
}
void PrintField::reprintCell(int x, int y, const Cell& cell) {
    setCursorposition(x, y);
    std::cout << CellRegister::getSymb(cell);
}

void PrintField::setCursorposition(int x, int y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ static_cast<SHORT>(x), static_cast<SHORT>(y) });

}