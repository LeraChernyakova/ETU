#pragma once
#include "LevelInterface.h"

class SecondLevel: public LevelInterface {
public:
    SecondLevel(Observable *observable);
    void react1(std::string type, MessageInfo info, Logger* log, int a) final;
    void gameState(std::string type, MessageInfo info, Logger* log);
    void react(MessageInfo info, Logger* log, int a) final;
};


