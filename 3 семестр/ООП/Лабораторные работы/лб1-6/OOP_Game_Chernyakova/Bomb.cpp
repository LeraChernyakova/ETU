#include "Bomb.h"

void Bomb::event() {
    if (!active)
        return;
    active = false;
    if (observer)
        observer->onBombEventInvoked();
    if (player->getProtection() <= 3) {
        player->changeLives(-1);
        player->changeProtection(-1);
    }

}
Bomb::Bomb(Player* player, IBombEventObserver* observer) : IPlayerEvent(player), observer(observer) {}

IEvent* Bomb::clone() {
    return new Bomb(player, observer);
}
void Bomb::setObserver(IBombEventObserver* obs) {
    observer = obs;
}
bool Bomb::isActive() {
    return active;
}