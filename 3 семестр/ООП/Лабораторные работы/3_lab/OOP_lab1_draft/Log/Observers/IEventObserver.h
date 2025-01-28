#pragma once

#include "..\Log.h"

class IEventObserver {
public:
    virtual void caveAction(Log &log) = 0;
    virtual void clanAction(Log &log) = 0;
    virtual void exitAction(Log &log) = 0;
    virtual void hungryAction(Log &log) = 0;
    virtual void resourceAction(Log &log) = 0;
    virtual ~IEventObserver() = default;
};

