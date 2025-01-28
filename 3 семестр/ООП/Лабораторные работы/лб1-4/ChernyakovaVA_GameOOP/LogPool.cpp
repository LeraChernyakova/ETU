#include "LogPool.h"

#include <utility>


bool LogPool::is_logging(Levels lvl) {
    for (Levels cur : levels) {
        if (cur == lvl)
            return true;
    }
    return false;
}

void LogPool::set_log_levels(std::vector<Levels> vec) {
    levels = std::move(vec);
}

void LogPool::update() {
    if (is_logging(factory->get_message().get_level()))
        print_log(factory->get_message());
}

void LogPool::add_log_level(Levels lvl) {
    levels.push_back(lvl);
}

void LogPool::print_log(Message& msg) {
    for (ILogger* obj : loggers) {
        obj->print(msg);
    }
}

LogPool::LogPool(MessageFactory* fact) : factory(fact) {
    MessageFactory::get_instance().attach(this);
}
