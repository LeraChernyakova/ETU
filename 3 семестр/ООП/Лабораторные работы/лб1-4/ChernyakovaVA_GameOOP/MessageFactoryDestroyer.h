#pragma once

class MessageFactory;
#include "MessageFactory.h"

class MessageFactoryDestroyer {
private:
    MessageFactory* p_factory;
public:
    void initialize(MessageFactory* pointer);
    ~MessageFactoryDestroyer();
};