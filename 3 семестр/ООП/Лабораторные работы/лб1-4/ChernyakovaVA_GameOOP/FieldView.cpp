#include "FieldView.h"

void FieldView::write_field() const {
    system("cls");
    for (int i = 0; i != field->get_height(); ++i) {
        for (int j = 0; j != field->get_width(); ++j) {
            if (i == field->get_position().second && j == field->get_position().first) {
                std::cout << "|P|";
            }
            else {
                std::cout << "|";
                std::cout << CellView(field->get_cell(j, i)).get_view();
                std::cout << "|";
            }
        }
        std::cout << "\n";
    }
}


FieldView::FieldView(Field* map) : field(map) {
    field->attach(this);
}

void FieldView::update() {
    write_field();
}
