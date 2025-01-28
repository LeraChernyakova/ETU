#pragma once

#include "IWaterEventObserver.h"
#include "Logger.h"

class WaterEventObserver : public IWaterEventObserver {
public:
    void onWaterEventInvoked()override;
};