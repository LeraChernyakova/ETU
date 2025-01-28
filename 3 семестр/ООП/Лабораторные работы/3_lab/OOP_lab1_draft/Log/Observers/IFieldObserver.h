#pragma once

#include "../Log.h"

class IFieldObserver {
public:
    virtual void openExit() = 0;
    virtual void changedPlayerPosition(int x_position, int y_position) = 0;
    virtual void stepOnBarrier() = 0;
    virtual ~IFieldObserver() = default;
};

