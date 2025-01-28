#pragma once

#include "ILogger.h"
#include <iostream>


class ConsoleLogger : public ILogger {
public:
    ILogger &operator<<(Message message) final;
};


