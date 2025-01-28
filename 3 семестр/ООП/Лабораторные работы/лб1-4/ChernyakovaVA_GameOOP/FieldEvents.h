#pragma once

class Field;

#include "Event.h"

class FieldEvents : public Event {
protected:
    Field* field;
public:
    virtual void execute() = 0;
    virtual ~FieldEvents() = default;
};
