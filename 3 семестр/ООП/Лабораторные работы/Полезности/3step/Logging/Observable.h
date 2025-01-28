#pragma once
#include "MessageInfo.h"
#include "Logger.h"

class Observable {
public:
    virtual ~Observable()=default;
    virtual void sortMessages(int number, std::string message, MessageInfo info, Logger* log)=0;
};


