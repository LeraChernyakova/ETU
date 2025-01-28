
#ifndef OOP_LAB1_LOG_H
#define OOP_LAB1_LOG_H

#include "Message.h"
#include "ILogger.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include <map>

class Log {
private:
    ILogger **loggers_array;
    Level level;
    int number_of_loggers;
public:
    Log();
    Log(Level level_choose, bool file_logger, bool console_logger);
    void viewMessage(const Message& message);
    ~Log();
};


#endif //OOP_LAB1_LOG_H
