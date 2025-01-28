#pragma once

struct InputMessage;

class IInputMediator {
public:
    virtual void process(const InputMessage& message) = 0;
};
