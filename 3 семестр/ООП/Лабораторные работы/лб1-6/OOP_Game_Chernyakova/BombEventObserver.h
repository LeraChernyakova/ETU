#pragma once

#include "IBombEventObserver.h"
#include "Logger.h"

class BombEventObserver :public IBombEventObserver {
public:
    void onBombEventInvoked()override;

};