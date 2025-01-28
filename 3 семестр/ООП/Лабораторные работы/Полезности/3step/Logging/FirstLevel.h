#pragma once
#include "LevelInterface.h"

class FirstLevel: public LevelInterface {
   public:
    FirstLevel(Observable *observable);
    void react(MessageInfo info, Logger* log, int a) final;
    void react1(std::string type, MessageInfo info, Logger* log, int a) final;
    void changeCell(MessageInfo info, Logger* log);
    void changePlayer(std::string type, MessageInfo info, Logger* log);
    void eventHappened(std::string type, MessageInfo info, Logger* log);
    void exitOpen(MessageInfo info, Logger* log);
};


