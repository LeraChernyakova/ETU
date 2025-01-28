#pragma once

#include "PlayerController.h"
#include "Field.h"
#include "IEvent.h"
class IFieldControllerEvent : public IEvent {
public:
    explicit IFieldControllerEvent(PlayerController* controller, Field* field);
    void event() = 0;
    IEvent* clone() override = 0;
    bool isActive() override = 0;
protected:
    PlayerController* controller;
    Field* field;
};