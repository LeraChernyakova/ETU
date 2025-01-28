#pragma once

#include "FieldScheme.h"
#include "Field.h"

class FieldRegister {
public:
    static FieldScheme getScheme(const Field& field);
};
