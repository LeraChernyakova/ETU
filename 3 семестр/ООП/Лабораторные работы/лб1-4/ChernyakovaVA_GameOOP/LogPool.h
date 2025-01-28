#pragma once

class Message;
class MessageFactory;

#include "ConsoleLog.h"
#include "Message.h"
#include <vector>
#include <algorithm>
#include "Levels.h"
#include "IObserver.h"
#include "MessageFactory.h"

class LogPool : public IObserver {
private:
    std::vector<ILogger*> loggers;
    std::vector<Levels> levels;
    MessageFactory* factory;
    bool is_logging(Levels);
public:
    explicit LogPool(MessageFactory*);
    void add_log_level(Levels);
    void set_log_levels(std::vector<Levels>);
    void update() final;
    template<typename T>
    void add_logger() {
        if (std::is_base_of<ILogger, T>::value)
            loggers.push_back(new T);
    }

    template<typename T>
    void add_logger(std::string filename) {
        if (std::is_base_of<ILogger, T>::value)
            loggers.push_back(new T(filename));
    }

    void print_log(Message& msg);

    ~LogPool() {
        std::for_each(loggers.begin(), loggers.end(), [](ILogger* obj) {delete obj; });
    }
};