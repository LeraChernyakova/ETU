#pragma once

#include "Logger.h"
#include "IPlayerEvent.h"
#include "IWaterEventObserver.h"

class Water : public IPlayerEvent {
public:
    void event() override;
    Water(Player* player, IWaterEventObserver* observer = nullptr);
    IEvent* clone() override;
    void setObserver(IWaterEventObserver* obs);
    bool isActive() override;
private:
    IWaterEventObserver* observer;
    bool active = true;

};