#pragma once

#include "IFieldObserver.h"
#include <iostream> 
#include <string>

class FieldObserver : public IFieldObserver{
private:
    Log log;
public:
    explicit FieldObserver(Log &log_);
    void openExit() final;
    void changedPlayerPosition(int x_position, int y_position) final;
    void stepOnBarrier() final;
};

