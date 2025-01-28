#include "Message.h"

Message::Message(Levels lvl, const std::string& msg) {
    level = lvl;
    text = msg;
}

Levels Message::get_level() const {
    return level;
}

std::string Message::get_text() const {
    return text;
}

void Message::set_level(Levels lvl) {
    level = lvl;
}

std::string Message::get_prefix() const {
    return prefixs.at(this->level);
}

std::ostream& operator<<(std::ostream& os, const Message& obj) {
    os << obj.get_prefix();
    os << " ";
    os << obj.get_text();
    os << std::endl;
    return os;
}