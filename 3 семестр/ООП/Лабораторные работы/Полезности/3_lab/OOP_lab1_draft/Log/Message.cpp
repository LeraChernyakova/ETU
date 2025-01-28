
#include "Message.h"


std::string &Message::getMessage() {
    return message;
}

Level Message::getLevel() const {
    return level;
}

Message::Message(std::string message, Level level) : message(std::move(message)), level(level) {}


