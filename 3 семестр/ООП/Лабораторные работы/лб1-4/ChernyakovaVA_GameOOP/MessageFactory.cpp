#include "MessageFactory.h"

MessageFactory* MessageFactory::p_factory = nullptr;
MessageFactoryDestroyer MessageFactory::destroyer;

MessageFactory& MessageFactory::get_instance() {
    if (p_factory == nullptr) {
        p_factory = new MessageFactory();
        destroyer.initialize(p_factory);
    }
    return *p_factory;
}

void MessageFactory::create_message(Levels lvl, const std::string& text) {
    delete msg;
    msg = new Message(lvl, text);
    this->notify();
}

Message& MessageFactory::get_message() {
    return *msg;
}

MessageFactory::~MessageFactory() {
    delete msg;
}