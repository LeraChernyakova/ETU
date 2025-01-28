#pragma once

#include "IEventObserver.h"
class ITeleportEventObserver :public IEventObserver {
public:
    virtual void onTeleportEventInvoked() = 0;
};