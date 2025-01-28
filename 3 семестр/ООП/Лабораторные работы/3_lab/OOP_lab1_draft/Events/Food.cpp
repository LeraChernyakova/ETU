
#include "Food.h"

void Food::addGood(Player &player, Log &log) {
    player.addPlayerHealth(1);
    player.addPlayerPoints(10);
}

void Food::playerReact(Player &player, Log &log) {
    event_observer->foodAction(log);
    this->addGood(player, log);
    this->addPoints(player, log);
    if (player.getPoints() > 130 && !player.getOpenExit())
        player.setOpenExit();
}

Food::Food() {
    event_observer = new EventObserver;
}

Food::~Food() {
    delete event_observer;
}
