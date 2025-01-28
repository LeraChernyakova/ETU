#pragma once

#include "IInputMediator.h"

class InputReader {
public:
    explicit InputReader(IInputMediator* mediator);
    virtual void readCommand() = 0;

protected:
    IInputMediator* mediator;
};