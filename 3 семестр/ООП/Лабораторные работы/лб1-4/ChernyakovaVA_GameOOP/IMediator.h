#pragma once

class MediatorObject;
class LogPool;
#include "MediatorObject.h"

class IMediator {
public:
    enum MEVENTS {
        GAME_STATUS,
        LEVEL,
        FIELD,
        STEP
    };
    IMediator() = default;
    virtual void notify(MediatorObject* who, MEVENTS event) = 0;
    virtual void set_log(LogPool*) = 0;
    virtual ~IMediator() = default;
};
