#include "Message.h"
#include <iostream>
#pragma once

class LevelInterface {
protected:
    Observable* observable;
public:
    LevelInterface(Observable* observable);
    virtual ~LevelInterface()=default;
    virtual void react(MessageInfo info, Logger* log, int a)=0;
    virtual void react1(std::string type, MessageInfo info, Logger* log, int a)=0;
};

