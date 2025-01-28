#include "FirstLevel.h"

FirstLevel::FirstLevel(Observable *observable) : LevelInterface(observable){};

void FirstLevel::changeCell(MessageInfo info, Logger* log){
    std::string a="[PlayerState] The player moved";
    observable->sortMessages(1,a,info, log);
};
void FirstLevel::changePlayer(std::string type, MessageInfo info, Logger* log){
    std::string a="[PlayerState] Player's characteristic changed: "+type;
    observable->sortMessages(1,a,info, log);
};
void FirstLevel::eventHappened(std::string type, MessageInfo info, Logger* log){
    std::string a="[FieldState] Event "+type+" happened";
    observable->sortMessages(1,a,info, log);
};

void FirstLevel::exitOpen(MessageInfo info, Logger* log){
    observable->sortMessages(1,"[FieldState] The exit is open, don't loose ur cash",info, log);
}

void FirstLevel::react(MessageInfo info, Logger* log, int a){
    switch(a){
        case 1:
            changeCell(info, log);
            break;
        case 2:
            exitOpen(info, log);
            break;
    }
};
void FirstLevel::react1(std::string type, MessageInfo info, Logger* log, int a){
    switch(a){
        case 1:
            changePlayer(type, info, log);
            break;
        case 2:
            eventHappened(type, info, log);
            break;
    }
};