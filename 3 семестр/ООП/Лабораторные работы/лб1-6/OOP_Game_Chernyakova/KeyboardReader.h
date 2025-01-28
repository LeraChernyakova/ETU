#pragma once

#include "InputReader.h"
#include "ControlScheme.h"

class KeyboardReader : public InputReader {
public:
    KeyboardReader(IInputMediator* mediator);
    void readCommand() override;
    void setScheme(const ControlScheme& scheme);
private:
    ControlScheme scheme;
};