
#include "Trap.h"

void Trap::remBad(Player &player, Log &log) {
    player.remPlayerProtection(10);
}

void Trap::playerReact(Player &player, Log &log) {
    event_observer->trapAction(log);
    this->remBad(player, log);
    this->remPoints(player, log);
    if (player.getHealth() < 1 or player.getPoints() < 1 or player.getProtection() < 1)
        player.setDead();
}

Trap::Trap() {
    event_observer = new EventObserver;
}

Trap::~Trap() {
    delete event_observer;
}
