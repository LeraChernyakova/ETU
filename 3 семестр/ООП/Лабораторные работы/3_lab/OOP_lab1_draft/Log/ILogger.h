#pragma once

#include "Message.h"

class ILogger {
public:
    virtual ILogger &operator<<(Message message) = 0;
    virtual ~ILogger() = default;
};

