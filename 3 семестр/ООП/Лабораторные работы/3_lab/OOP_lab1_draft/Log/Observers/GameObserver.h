#pragma once

#include "IGameObserver.h"

class GameObserver : public IGameObserver{
public:
    void gameStarted(Log &log) final;
    void gameEnded(Log &log) final;
    void invalidFieldHeight(Log &log) final;
    void invalidFieldWidth(Log &log) final;
};

