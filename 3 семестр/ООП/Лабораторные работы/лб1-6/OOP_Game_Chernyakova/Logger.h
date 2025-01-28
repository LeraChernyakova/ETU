#pragma once


#include <unordered_set>
#include "ILogger.h"

struct LogMessage;
class Logger {
public:
    enum Level {
        Trace,
        Info,
        Error
    };
    Logger& operator<<(const LogMessage& message);
    void addLogger(ILogger* logger);
    void removeLogger(ILogger* logger);
    void setLevel(Level level);
    static Logger& getInstance();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    static std::string levelToString(Level level);
    void setOffset(int offset);
    ~Logger();
private:
    Logger() = default;
    Level level;
    std::unordered_set<ILogger*> loggers;
};
struct LogMessage {
    std::string message;
    Logger::Level level;
};