
#include "GameObserver.h"

void GameObserver::gameStarted(Log &log) {
    Message message = Message("Game started", Level::INFO);
    log.viewMessage(message);
}

void GameObserver::gameEnded(Log &log) {
    Message message = Message("Game ended", Level::INFO);
    log.viewMessage(message);
}

void GameObserver::invalidFieldHeight(Log &log) {
    Message message = Message("You entered invalid field height!", Level::ERROR_INFO);
    log.viewMessage(message);
}

void GameObserver::invalidFieldWidth(Log &log) {
    Message message = Message("You entered invalid field width!", Level::ERROR_INFO);
    log.viewMessage(message);
}
