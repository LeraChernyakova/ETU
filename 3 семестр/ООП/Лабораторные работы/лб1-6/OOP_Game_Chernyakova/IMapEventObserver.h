#pragma once

#include "IEventObserver.h"
class IMapEventObserver :public IEventObserver {
public:
    virtual void onMapEventInvoked() = 0;
};