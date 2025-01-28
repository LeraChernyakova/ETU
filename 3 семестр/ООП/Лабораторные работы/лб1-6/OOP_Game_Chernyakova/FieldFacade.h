#pragma once

#include "Field.h"

class FieldFacade {
public:
    FieldFacade();
    FieldFacade(Field* field);
    FieldFacade(int width, int height);
    Field& getField();
private:
    Field* field;
};