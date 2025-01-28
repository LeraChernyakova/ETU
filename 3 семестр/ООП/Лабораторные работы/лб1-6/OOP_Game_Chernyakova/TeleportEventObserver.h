#pragma once

#include "Logger.h"
#include "ITeleportEventObserver.h"
class TeleportEventObserver :public ITeleportEventObserver {
public:
    void onTeleportEventInvoked()override;
};