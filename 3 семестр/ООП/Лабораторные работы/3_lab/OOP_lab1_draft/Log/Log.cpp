#include "Log.h"
#include <algorithm>


Log::Log() {
    loggers = {};
    levels = {};
    is_console = false;
}

Log::Log(bool level_trace, bool level_info, bool level_error, bool file_logger, bool console_logger) {
    if (level_trace)
        this->addLevel(Level::TRACE);
    if (level_info)
        this->addLevel(Level::INFO);
    if (level_error)
        this->addLevel(Level::ERROR_INFO);
    if (file_logger) {
        ILogger *file_log = new FileLogger;
        this->addLogger(file_log);
    }
    if (console_logger) {
        is_console = true;
        ILogger *console_log = new ConsoleLogger;
        this->addLogger(console_log);
    }
}

void Log::viewMessage(const Message &message) {
    for (auto &logger: loggers) {
        for (auto &level: levels) {
            if (message.getLevel() == level) {
                if (is_console){
                    *logger << message;
                    system("pause");
                }
                else
                    *logger << message;
            }
        }
    }
}

Log::~Log() {
//    for (auto & logger : loggers){
//        delete logger;
//    }
}

void Log::addLevel(Level level) {
    levels.push_back(level);
}

void Log::addLogger(ILogger *logger) {
    loggers.push_back(logger);
}

