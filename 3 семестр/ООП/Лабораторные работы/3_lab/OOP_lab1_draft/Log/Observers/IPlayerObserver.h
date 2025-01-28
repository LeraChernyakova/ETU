#pragma once

#include "../Log.h"

class IPlayerObserver {
public:
    virtual void changedScore(int score) = 0;
    virtual void changedFood(int food) = 0;
    virtual void changedHealth(int health) = 0;
    virtual void playerWon() = 0;
    virtual void playerLost() = 0;
    virtual ~IPlayerObserver() = default;
};

