#pragma once
#include "Observable.h"

class Message: public Observable {
public:
     void sortMessages(int number, std::string message, MessageInfo info, Logger* log) final;
};

