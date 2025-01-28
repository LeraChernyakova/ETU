#pragma once

#include "IEventObserver.h"

class EventObserver : public IEventObserver{
private:
    bool isActive;
public:
    void caveAction(Log &log) final;
    void clanAction(Log &log) final;
    void exitAction(Log &log) final;
    void hungryAction(Log &log) final;
    void resourceAction(Log &log) final;
};

