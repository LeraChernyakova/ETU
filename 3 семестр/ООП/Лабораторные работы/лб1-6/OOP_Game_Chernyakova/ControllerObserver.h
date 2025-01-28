#pragma once

#include "IControllerObserver.h"

class ControllerObserver : public IControllerObserver {
public:
    void onPlayerPositionChanged(int pos_x, int pos_y) override;
    void impassableCellWarning(int pos_x, int pos_y)override;
    //IControllerObserver& operator<<(const PlayerController& playerController) override;
};