#include "KeyEvent.h"

void KeyEvent::event() {
    if (!active) {
        return;
    }
    active = false;
    player->foundKey();
    if (observer)
        observer->onKeyEventInvoked();
}
KeyEvent::KeyEvent(Player* player, IKeyEventObserver* observer) : IPlayerEvent(player), observer(observer) {}

IEvent* KeyEvent::clone() {
    return new KeyEvent(player, observer);
}
void KeyEvent::setObserver(IKeyEventObserver* obs) {
    observer = obs;
}
bool KeyEvent::isActive() {
    return active;
}