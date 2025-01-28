#pragma once

#include "IEventObserver.h"

class IDoorEventObserver : public IEventObserver {
public:
    virtual void onDoorEventInvoked() = 0;
};