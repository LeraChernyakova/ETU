
#include "EventObserver.h"

void EventObserver::enemyAction(Log &log) {
    Message message = Message("Enemy event is active", Level::TRACE);
    log.viewMessage(message);
}

void EventObserver::trapAction(Log &log) {
    Message message = Message("Trap event is active", Level::TRACE);
    log.viewMessage(message);
}

void EventObserver::foodAction(Log &log) {
    Message message = Message("Food event is active", Level::TRACE);
    log.viewMessage(message);
}

void EventObserver::moneyAction(Log &log) {
    Message message = Message("Money event is active", Level::TRACE);
    log.viewMessage(message);
}

void EventObserver::exitAction(Log &log) {
    Message message = Message("Exit event is active", Level::TRACE);
    log.viewMessage(message);
}
