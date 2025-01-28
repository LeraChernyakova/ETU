#include "SecondLevel.h"

SecondLevel::SecondLevel(Observable *observable) : LevelInterface(observable){};

void SecondLevel::gameState(std::string type, MessageInfo info, Logger* log){
    std::string a="[GameStatus] Game state changed to: "+type;
    observable->sortMessages(2, a, info, log);
};

void SecondLevel::react1(std::string type, MessageInfo info, Logger* log, int a){
    gameState(type, info, log);
};

void SecondLevel::react(MessageInfo info, Logger* log, int a){};
