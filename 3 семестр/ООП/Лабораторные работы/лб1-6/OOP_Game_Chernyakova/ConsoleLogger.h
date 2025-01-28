#pragma once

#include "ILogger.h"
#include "Player.h"
#include "PlayerController.h"
#include "Field.h"
class ConsoleLogger : public ILogger {
public:
    ILogger& operator<<(const std::string& str) override;
    void setOffset(int offset) override;
private:
    int _offset;
    const int _max_offset = 5;
    int _count = 0;
};
