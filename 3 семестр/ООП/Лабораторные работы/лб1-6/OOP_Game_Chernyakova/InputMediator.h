#pragma once

#include <unordered_set>
#include "IInputMediator.h"
#include "InputReader.h"
#include "IController.h"

class InputMediator : public IInputMediator {
public:
    void process(const InputMessage& message) override;
    void tick();
    void addReader(InputReader* reader);
    void addController(IController* controller);
    void removeController(IController* controller);
private:
    InputReader* readers;
    std::unordered_set<IController*> controllers;
};