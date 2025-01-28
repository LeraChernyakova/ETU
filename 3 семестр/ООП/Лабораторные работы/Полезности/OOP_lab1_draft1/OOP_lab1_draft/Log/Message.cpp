
#include "Message.h"


std::string &Message::get_message() {
    return message;
}

Level Message::get_level() const {
    return level;
}

Message::Message(std::string &message, Level level) : message(std::move(message)), level(level) {}


