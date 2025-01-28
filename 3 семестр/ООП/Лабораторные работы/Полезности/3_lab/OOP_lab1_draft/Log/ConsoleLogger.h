
#ifndef OOP_LAB1_CONSOLELOGGER_H
#define OOP_LAB1_CONSOLELOGGER_H

#include "ILogger.h"
#include <iostream>


class ConsoleLogger : public ILogger {
public:
    ILogger &operator<<(Message message) final;
};


#endif //OOP_LAB1_CONSOLELOGGER_H
