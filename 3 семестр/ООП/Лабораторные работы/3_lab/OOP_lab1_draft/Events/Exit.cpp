
#include "Exit.h"

void Exit::playerReact(Player &player, Log &log) {
    event_observer->exitAction(log);
    player.setWin();
}

void Exit::addGood(Player &player, Log &log) {}

Exit::Exit() {
    event_observer = new EventObserver;
}

Exit::~Exit() {
    delete event_observer;
}

