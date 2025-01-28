#pragma once

class Game;
#include "Event.h"

class GameEvents : public Event {
protected:
    Game* game;
public:
    virtual void execute() = 0;
    virtual ~GameEvents() = default;
};