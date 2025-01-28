#include "ThirdLevel.h"

ThirdLevel::ThirdLevel(Observable *observable) : LevelInterface(observable){};

void ThirdLevel::gameError(std::string type, MessageInfo info, Logger* log){
    std::string a="[ProgramState] Error: "+type;
    observable->sortMessages(3,a, info, log);
};

void ThirdLevel::react(MessageInfo info, Logger* log, int a){};

void ThirdLevel::react1(std::string type, MessageInfo info, Logger* log, int a){
    gameError(type,info, log);
};