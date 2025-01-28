#include "DoorEvent.h"

void DoorEvent::event() {
    if (player->doorKey()) {
        player->victory();
        if (observer)
            observer->onDoorEventInvoked();
    }
    //    if(observer)
    //        observer->onDoorEventInvoked();
}
DoorEvent::DoorEvent(Player* player, IDoorEventObserver* observer) : IPlayerEvent(player), observer(observer) {}

IEvent* DoorEvent::clone() {
    return new DoorEvent(player, observer);
}
void DoorEvent::setObserver(IDoorEventObserver* obs) {
    observer = obs;
}
bool DoorEvent::isActive() {
    return true;
}