
#include "FieldObserver.h"

void FieldObserver::openExit(Log &log) {
    Message message = Message("Exit is open now.", Level::TRACE);
    log.viewMessage(message);
}

void FieldObserver::changedPlayerPosition(Log &log, int x_position, int y_position) {
    std::string str;
    str = "Player position changed. Player position: (" + std::to_string(x_position) + ", " + std::to_string(y_position) + ")";
    Message message = Message(str, Level::TRACE);
    log.viewMessage(message);
}

void FieldObserver::stepOnBarrier(Log &log) {
    Message message = Message("You tried to step on barrier!", Level::ERROR_INFO);
    log.viewMessage(message);
}
