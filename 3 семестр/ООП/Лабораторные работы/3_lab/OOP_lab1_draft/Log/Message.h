#pragma once

#include <iostream>
#include "Level.h"

class Message {
private:
    std::string message;
    Level level;

public:
    Message() = default;
    Message(std::string message, Level level);
    std::string& getMessage();
    Level getLevel() const;
};

