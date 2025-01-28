#pragma once

#include "IEventObserver.h"
class IKeyEventObserver :public IEventObserver {
public:
    virtual void onKeyEventInvoked() = 0;
};