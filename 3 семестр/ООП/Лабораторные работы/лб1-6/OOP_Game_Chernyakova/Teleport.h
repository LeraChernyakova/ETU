#pragma once

#include "IFieldControllerEvent.h"
#include "ITeleportEventObserver.h"
#include "Logger.h"

class Teleport : public IFieldControllerEvent {
public:
    void event() override;
    Teleport(PlayerController* controller, Field* field, ITeleportEventObserver* observer = nullptr);
    IEvent* clone() override;
    void setObserver(ITeleportEventObserver* obs);
    bool isActive() override;
private:
    ITeleportEventObserver* observer;

};