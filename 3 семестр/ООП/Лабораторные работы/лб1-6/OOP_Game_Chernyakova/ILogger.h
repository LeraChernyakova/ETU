#pragma once

#include <string>
class Player;
class PlayerController;
class Field;
class ILogger {
public:
    virtual ILogger& operator<<(const std::string& str) = 0;
    virtual void setOffset(int offset) = 0;
    virtual ~ILogger() = default;
};