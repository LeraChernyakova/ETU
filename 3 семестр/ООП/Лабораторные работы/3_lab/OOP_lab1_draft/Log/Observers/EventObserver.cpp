#include "EventObserver.h"

void EventObserver::caveAction(Log &log) {
    Message message = Message("[event_state]Cave event is active.", Level::TRACE);
    log.viewMessage(message);
}

void EventObserver::clanAction(Log &log) {
    Message message = Message("[event_state]Clan event is active.", Level::TRACE);
    log.viewMessage(message);
}

void EventObserver::exitAction(Log &log) {
    Message message = Message("[event_state]Exit event is active.", Level::TRACE);
    log.viewMessage(message);
}

void EventObserver::hungryAction(Log &log) {
    Message message = Message("[event_state]Hungry event is active", Level::TRACE);
    log.viewMessage(message);
}

void EventObserver::resourceAction(Log &log) {
    Message message = Message("[event_state]Resource event is active.", Level::TRACE);
    log.viewMessage(message);
}
