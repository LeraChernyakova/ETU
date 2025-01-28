#include "Water.h"
#include "PlayerFacade.h"

void Water::event() {
    if (!active) {
        return;
    }
    active = false;
    if (player->getLives() < 3)
        player->changeLives(1);
    if (observer)
        observer->onWaterEventInvoked();
}

IEvent* Water::clone() {
    return new Water(player, observer);
}
Water::Water(Player* player, IWaterEventObserver* observer) : IPlayerEvent(player), observer(observer) {}

void Water::setObserver(IWaterEventObserver* obs) {
    observer = obs;
}
bool Water::isActive() {
    return active;
}