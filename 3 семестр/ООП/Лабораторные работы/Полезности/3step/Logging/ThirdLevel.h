#pragma once
#include "LevelInterface.h"

class ThirdLevel: public LevelInterface {
public:
    ThirdLevel(Observable *observable);
    void react(MessageInfo info, Logger* log, int a) final;
    void gameError(std::string type,MessageInfo info, Logger* log);
    void react1(std::string type, MessageInfo info, Logger* log, int a) final;
};

