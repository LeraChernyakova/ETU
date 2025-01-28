#pragma once

#include "IKeyEventObserver.h"
#include "Logger.h"
class KeyEventObserver : public IKeyEventObserver {
    void onKeyEventInvoked()override;
};