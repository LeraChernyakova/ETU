#pragma once

#include "IController.h"
class Applications;

class GameController :public IController {
public:
    GameController(Applications& applications);
    void processCommand(const InputMessage& message);
private:
    Applications& app;
};