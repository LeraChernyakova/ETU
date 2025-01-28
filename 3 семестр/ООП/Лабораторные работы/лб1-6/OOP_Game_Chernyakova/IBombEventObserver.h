#pragma once

#include "IEventObserver.h"

class IBombEventObserver : public IEventObserver {
public:
    virtual void onBombEventInvoked() = 0;
};