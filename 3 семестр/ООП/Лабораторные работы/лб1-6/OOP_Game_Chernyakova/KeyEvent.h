#pragma once

#include "IPlayerEvent.h"
#include "Logger.h"
#include "IKeyEventObserver.h"
class KeyEvent : public IPlayerEvent {
public:
    void event()override;
    KeyEvent(Player* player, IKeyEventObserver* observer = nullptr);
    IEvent* clone() override;
    void setObserver(IKeyEventObserver* obs);
    bool isActive() override;
private:
    IKeyEventObserver* observer;
    bool active = true;
};