#pragma once

#include "Player.h"
#include "IPlayerEvent.h"
#include "IDoorEventObserver.h"
#include "Logger.h"
class DoorEvent : public IPlayerEvent {
public:
    void event() override;
    explicit DoorEvent(Player* player, IDoorEventObserver* observer = nullptr);
    IEvent* clone() override;
    void setObserver(IDoorEventObserver* obs);
    bool isActive() override;
private:
    IDoorEventObserver* observer;
};