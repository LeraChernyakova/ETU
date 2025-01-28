#include "MessageFactoryDestroyer.h"

void MessageFactoryDestroyer::initialize(MessageFactory* pointer) {
    p_factory = pointer;
}

MessageFactoryDestroyer::~MessageFactoryDestroyer() {
    delete p_factory;
}