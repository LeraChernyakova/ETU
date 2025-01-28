#pragma once

#include "IDoorEventObserver.h"
#include "Logger.h"

class DoorEventObserver :public IDoorEventObserver {
public:
    void onDoorEventInvoked()override;
};