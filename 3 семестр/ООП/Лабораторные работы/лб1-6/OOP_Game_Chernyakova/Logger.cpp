#include <iostream>
#include "Logger.h"

Logger& Logger::operator<<(const LogMessage& message) {
    if (message.level < level)
        return *this;
    for (auto logger : loggers) {
        *logger << (levelToString(message.level) + ": " + message.message);
    }
    return *this;
}
void Logger::addLogger(ILogger* logger) {
    loggers.insert(logger);
}
void Logger::removeLogger(ILogger* logger) {
    loggers.erase(logger);
}
Logger::~Logger() {
    for (auto logger : loggers) {
        delete logger;
    }
}
void Logger::setLevel(Logger::Level level) {
    this->level = level;
}
Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

//ворт деструктор в ILogger
std::string Logger::levelToString(Logger::Level level) {
    switch (level) {
    case Trace:
        return "[Trace]";
    case Info:
        return "[Info]";
    case Error:
        return "[Error]";
    default:
        return "[Unknown]";
    }
}
void Logger::setOffset(int offset) {
    for (auto& logger : loggers) {
        logger->setOffset(offset);
    }
}