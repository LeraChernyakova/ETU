
#ifndef OOP_LAB1_LOG_H
#define OOP_LAB1_LOG_H

#include "Message.h"
#include "ILogger.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include <map>
#include <vector>

class Log {
private:
    std::vector <ILogger*> loggers;
    std::vector <Level> levels;
    bool is_console;
public:
    Log();
    void addLevel(Level level);
    void addLogger(ILogger* logger);
    Log(bool level_trace, bool level_info, bool level_error, bool file_logger, bool console_logger);
    void viewMessage(const Message& message);
    ~Log();
};


#endif //OOP_LAB1_LOG_H
