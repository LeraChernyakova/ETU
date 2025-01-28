#include "GameObserver.h"

void GameObserver::gameStarted(Log &log) {
    Message message = Message("[game_state]Game started.", Level::INFO);
    log.viewMessage(message);
}

void GameObserver::gameEnded(Log &log) {
    Message message = Message("[game_state]Game ended.", Level::INFO);
    log.viewMessage(message);
}

void GameObserver::invalidFieldHeight(Log &log) {
    Message message = Message("[game_state]You entered invalid field height!", Level::ERROR_INFO);
    log.viewMessage(message);
}

void GameObserver::invalidFieldWidth(Log &log) {
    Message message = Message("[game_state]You entered invalid field width!", Level::ERROR_INFO);
    log.viewMessage(message);
}
