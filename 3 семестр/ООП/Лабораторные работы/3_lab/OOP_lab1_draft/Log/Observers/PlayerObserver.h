#pragma once

#include "IPlayerObserver.h"

class PlayerObserver : public IPlayerObserver{
private:
    Log log;
public:
    explicit PlayerObserver(Log &log_);
    void changedScore(int score) final;
    void changedFood(int food) final;
    void changedHealth(int health) final;
    void playerWon() final;
    void playerLost() final;
};
