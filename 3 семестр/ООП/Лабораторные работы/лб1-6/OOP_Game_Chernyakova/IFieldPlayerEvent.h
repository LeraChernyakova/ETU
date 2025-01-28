#pragma once

#include "Field.h"
#include "Player.h"
#include "IEvent.h"
class IFieldPlayerEvent : public IEvent {
public:
    explicit IFieldPlayerEvent(Field* field, Player* player);
    void event() = 0;
    IEvent* clone() override = 0;
    bool isActive() override = 0;
protected:
    Field* field;
    Player* player;
};