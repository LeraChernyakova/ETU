#pragma once

#include "IEventGen.h"
#include "Field.h"
#include "FieldNoWalls.h"

class FieldEventGen : public IEventGen {
public:
    explicit FieldEventGen(Field* pField) { field = pField; };
    Event* generate() final;
    ~FieldEventGen() override = default;
};