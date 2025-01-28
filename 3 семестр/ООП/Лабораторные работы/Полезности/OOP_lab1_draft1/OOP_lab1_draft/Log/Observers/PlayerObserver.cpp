
#include "PlayerObserver.h"

void PlayerObserver::changedPoints(Log &log, int points) {
    std::string str;
    str = "Player's points changed. Now there are " + std::to_string(points) + " points.";
    Message message = Message(str, Level::TRACE);
    log.viewMessage(message);
}

void PlayerObserver::changedProtection(Log &log, int protection) {
    std::string str;
    str = "Player's protection changed. Now there are " + std::to_string(protection) + " protection.";
    Message message = Message(str, Level::TRACE);
    log.viewMessage(message);
}

void PlayerObserver::changedHealth(Log &log, int health) {
    std::string str;
    str = "Player's health changed. Now there are " + std::to_string(health) + " health.";
    Message message = Message(str, Level::TRACE);
    log.viewMessage(message);
}

void PlayerObserver::playerWon(Log &log) {
    Message message = Message("Player won!", Level::TRACE);
    log.viewMessage(message);
}

void PlayerObserver::playerLost(Log &log) {
    Message message = Message("Player lost!", Level::TRACE);
    log.viewMessage(message);
}
