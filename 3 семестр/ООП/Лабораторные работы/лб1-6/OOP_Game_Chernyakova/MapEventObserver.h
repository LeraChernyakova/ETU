#pragma once

#include "IMapEventObserver.h"
#include "Logger.h"
class MapEventObserver :public IMapEventObserver {
public:
    void onMapEventInvoked()override;
};