
#ifndef OOP_LAB1_MESSAGE_H
#define OOP_LAB1_MESSAGE_H

#include <iostream>
#include "Level.h"

class Message {
private:
    std::string message;
    Level level;

public:
    Message() = default;
    Message(std::string &message, Level level);
    std::string& get_message();
    Level get_level() const;
};


#endif //OOP_LAB1_MESSAGE_H
