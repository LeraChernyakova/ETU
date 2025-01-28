#include "FieldNoWalls.h"


FieldNoWalls::FieldNoWalls(Field* fl) {
    field = fl;
}

void FieldNoWalls::execute() {
    field->remove_walls();
}