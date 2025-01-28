#include "FieldFacade.h"

FieldFacade::FieldFacade() {
    field = new Field();
}
Field& FieldFacade::getField() {
    return *field;
}
FieldFacade::FieldFacade(int width, int height) {
    field = new Field(width, height);
}
FieldFacade::FieldFacade(Field* field) {
    this->field = field;
}