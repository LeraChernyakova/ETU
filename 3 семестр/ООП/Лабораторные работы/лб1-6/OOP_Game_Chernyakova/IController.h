#pragma once

#include "InputMessage.h"
class IController {
public:
    virtual void processCommand(const InputMessage& message) = 0;
};