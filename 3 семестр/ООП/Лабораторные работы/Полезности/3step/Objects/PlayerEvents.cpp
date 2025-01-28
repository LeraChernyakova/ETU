#include "PlayerEvents.h"

PlayerEvents::PlayerEvents(int exit, int hole, int exitP): exit(exit), hole(hole), exitP(exitP){};

int  PlayerEvents::getExit(){
    return exit;
};

int PlayerEvents::increaseExit(int increase){
    exit=increase;
};

void PlayerEvents::changeExitP(){
    exitP=1;
};

void PlayerEvents::increaseHole(int increase){
    hole=increase;
};

int PlayerEvents::getHole(){
    return hole;
}

int PlayerEvents::getExitP(){
    return exitP;
};
