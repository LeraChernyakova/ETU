#pragma once

#include "FieldScheme.h"

class IFieldGenerator {
public:
    virtual FieldScheme make() = 0;
    virtual ~IFieldGenerator() = default;
};