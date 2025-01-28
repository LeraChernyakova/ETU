#pragma once

#include "FieldEvents.h"
#include "Field.h"

class FieldNoWalls : public FieldEvents {
public:
    FieldNoWalls(Field* fl);
    void execute() final;
    ~FieldNoWalls() override = default;
};