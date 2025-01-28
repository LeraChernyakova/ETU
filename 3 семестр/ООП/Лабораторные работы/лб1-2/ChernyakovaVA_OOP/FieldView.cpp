#include "FieldView.h"

#include <iostream>

void FieldView::printLine(int width) {
    while (width > 0) {
        for (int i = 0; i < 3; i++)
            std::cout << "-";
        width--;
    }
    std::cout << '\n';
}

void FieldView::printField(Field& field) {
    system("cls");
    CellView cell_view;
    for (int i = 0; i < field.getHeight(); i++) {
        printLine(field.getWidth());
        for (int j = 0; j < field.getWidth(); j++) {
            cell_view.printCell(field.getCell(i, j));
        }
        std::cout << "\n";
    }
    printLine(field.getWidth());
}
