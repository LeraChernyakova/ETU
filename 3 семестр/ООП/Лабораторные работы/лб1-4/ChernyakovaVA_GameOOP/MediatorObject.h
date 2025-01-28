#pragma once

class IMediator;

#include "IMediator.h"

class MediatorObject {
public:
    MediatorObject(IMediator* med = nullptr);
    void set_mediator(IMediator* med);
    virtual ~MediatorObject() = default;
protected:
    IMediator* mediator;
};