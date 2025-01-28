
#ifndef OOP_LAB1_ILOGGER_H
#define OOP_LAB1_ILOGGER_H

#include "Message.h"

class ILogger {
public:
    virtual ILogger &operator<<(Message message) = 0;
    virtual ~ILogger() = default;
};


#endif //OOP_LAB1_ILOGGER_H
