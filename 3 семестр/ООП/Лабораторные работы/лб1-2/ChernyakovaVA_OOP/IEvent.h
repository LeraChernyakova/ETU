#pragma once
#include "Player.h"

class IEvent {
public:
    virtual void reaction(Player& player) = 0;// = 0 означает, что функция "чисто виртуальная"
    virtual ~IEvent() {};
};
