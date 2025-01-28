#include "EventObserverPool.h"

EventObserverPool::~EventObserverPool() {
    for (auto& value : _observers)
        delete value.second;
}

EventObserverPool& EventObserverPool::instance() {
    static EventObserverPool obj;
    return obj;
}