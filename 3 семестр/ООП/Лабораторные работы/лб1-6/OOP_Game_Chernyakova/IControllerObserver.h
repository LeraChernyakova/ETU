#pragma once

class PlayerController;
class IControllerObserver {
public:
    virtual void onPlayerPositionChanged(int pos_x, int pos_y) = 0;
    virtual void impassableCellWarning(int pos_x, int pos_y) = 0;
    // virtual IControllerObserver& operator<<(const PlayerController& playerController) = 0;
};
