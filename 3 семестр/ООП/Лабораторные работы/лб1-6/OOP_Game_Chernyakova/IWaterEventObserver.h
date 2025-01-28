#pragma once

#include "IEventObserver.h"

class IWaterEventObserver : public IEventObserver {
public:
    virtual void onWaterEventInvoked() = 0;
};