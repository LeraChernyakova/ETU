#pragma once

#include <iostream>
#include "ILogger.h"
#include "Message.h"

class ConsoleLog final : public ILogger {
public:
    ConsoleLog() = default;
    void print(const Message& msg) override;
    ~ConsoleLog() override = default;
};
