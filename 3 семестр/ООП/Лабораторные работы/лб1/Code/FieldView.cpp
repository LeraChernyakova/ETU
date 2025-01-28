#include "FieldView.h"

void FieldView::drawField() {
	for (int i = 0; i < field.getHeight(); i++) {
		for (int j = 0; j < field.getWidth(); j++) {

			if (field.getCells()[i][j].getType() == "player") {
				std::cout << "P";
			}
			if (field.getCells()[i][j].getType() == "border") {
				std::cout << "#";
			}
			if (field.getCells()[i][j].getType() == "rock") {
				std::cout << "R";
			}
			if (field.getCells()[i][j].getType() == "nothing") {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
}

void FieldView::setField(Field field_){
	field = field_;
}
