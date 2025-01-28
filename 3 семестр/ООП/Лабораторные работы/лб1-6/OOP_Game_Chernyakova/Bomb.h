#pragma once

#include "IPlayerEvent.h"
#include "IBombEventObserver.h"
#include "Logger.h"
class Bomb : public IPlayerEvent {
public:
    void event() override;
    Bomb(Player* player, IBombEventObserver* observer = nullptr);
    IEvent* clone() override;
    void setObserver(IBombEventObserver* obs);
    bool isActive() override;
private:
    IBombEventObserver* observer;
    bool active = true;
};