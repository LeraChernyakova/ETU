#include "PrintField.h"

#include <iostream>

void PrintField::printLine(int width) {
    std::cout << "+";
    while (width > 0) {
        for (int i = 0; i < 3; i++)
            std::cout << "-";
        std::cout << "+";
        width--;
    }
    std::cout << '\n';
//    std::cout << "-" * 4 * width << '\n';
}

void PrintField::print(Field &field) {
//    Sleep(500);
    system("cls");
    PrintCell print_cell;
    for (int i = 0; i < field.getHeight(); i++) {
        printLine(field.getWidth());
        for (int j = 0; j < field.getWidth(); j++) {
            print_cell.printCell(field.getCell(i, j));
        }
        std::cout << "|\n";
    }
    printLine(field.getWidth());
}

PrintField::PrintField() = default;

void PrintField::gotoxy(int x, int y) {
    COORD CursorPosition;
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void PrintField::setcursor(bool visible, DWORD size) {
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}
