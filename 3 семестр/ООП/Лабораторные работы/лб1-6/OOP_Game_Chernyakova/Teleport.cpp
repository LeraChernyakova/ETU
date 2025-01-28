#include "Teleport.h"

void Teleport::event() {
    controller->moveTo(0, 0);
    if (observer)
        observer->onTeleportEventInvoked();
}
Teleport::Teleport(PlayerController* controller, Field* field, ITeleportEventObserver* observer)
    : IFieldControllerEvent(controller, field),
    observer(observer) {}

IEvent* Teleport::clone() {
    return new Teleport(controller, field, observer);
}
void Teleport::setObserver(ITeleportEventObserver* obs) {
    observer = obs;
}
bool Teleport::isActive() {
    return true;
}