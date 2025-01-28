#include "FieldObserver.h"

void FieldObserver::openExit() {
    Message message = Message("[field_state]Exit is open now.", Level::TRACE);
    log.viewMessage(message);
}

void FieldObserver::changedPlayerPosition(int x_position, int y_position) {
    std::string str;
    str = "[field_state]Player position changed. Player position: (" + std::to_string(x_position) + ", " + std::to_string(y_position) + ").";
    Message message = Message(str, Level::TRACE);
    log.viewMessage(message);
}

void FieldObserver::stepOnBarrier() {
    Message message = Message("[field_state]You tried to step on barrier!", Level::ERROR_INFO);
    log.viewMessage(message);
}

FieldObserver::FieldObserver(Log &log_) {
    log = log_;
}
