#pragma once

#include "GameEvents.h"
#include "Game.h"

class WinEvent : public GameEvents {
public:
    explicit WinEvent(Game* gm);
    void execute() override;
};