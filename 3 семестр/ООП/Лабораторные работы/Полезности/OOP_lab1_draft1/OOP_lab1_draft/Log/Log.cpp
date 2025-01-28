
#include "Log.h"
#include <typeinfo>


Log::Log() {
    int number_of_loggers = 0;
    loggers_array = nullptr;
    level = Level::TRACE;
}

Log::Log(Level level_choose, bool file_logger, bool console_logger) {
    level = level_choose;
    if (file_logger and console_logger) {
        loggers_array = new ILogger *[2];
        loggers_array[0] = new FileLogger();
        loggers_array[1] = new ConsoleLogger();
        number_of_loggers = 2;
    }
    if (file_logger and !console_logger) {
        loggers_array = new ILogger *[1];
        loggers_array[0] = new FileLogger();
        number_of_loggers = 1;
    }
    if (!file_logger and console_logger) {
        loggers_array = new ILogger *[1];
        loggers_array[0] = new ConsoleLogger();
        number_of_loggers = 1;
    }
    if(!file_logger and !console_logger){
        number_of_loggers = 0;
        loggers_array = nullptr;
    }

}

void Log::viewMessage(const Message &message) {
    for (int i = 0; i < number_of_loggers; i++) {
        if (message.get_level() < level)
            return;
        (*loggers_array[i]) << message;
    }
}

Log::~Log() {
    for (int i = 0; i < number_of_loggers; i++){
        delete loggers_array[i];
    }
    delete[] loggers_array;
}

