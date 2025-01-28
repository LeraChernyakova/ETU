
#include "Money.h"

void Money::addGood(Player &player, Log &log) {
    player.addPlayerPoints(15, log);

}

void Money::playerReact(Player &player, Log &log) {
    event_observer->moneyAction(log);
    this->addGood(player, log);
    this->addPoints(player, log);
    if (player.getPoints() > 130 and !player.getOpenExit())
        player.setOpenExit();
}

Money::Money() {
    event_observer = new EventObserver;
}

Money::~Money(){
    delete event_observer;
}