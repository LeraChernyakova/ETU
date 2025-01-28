#pragma once

class Event;
class Field;
#include "RNGenerator.h"

class IEventGen {
protected:
    RNGenerator generator;
    Field* field;
public:
    IEventGen() : generator(), field(nullptr) {};
    virtual Event* generate() = 0;
    virtual ~IEventGen() = default;
};