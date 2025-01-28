
#include "PlayerObserver.h"
#include <string>

void PlayerObserver::changedScore(int score) {
    std::string str;
    str = "[player_state]Player's score changed. Now there are " + std::to_string(score) + " score.";
    Message message = Message(str, Level::TRACE);
    log.viewMessage(message);
}

void PlayerObserver::changedFood(int food) {
    std::string str;
    str = "[player_state]Player's food changed. Now there are " + std::to_string(food) + " food.";
    Message message = Message(str, Level::TRACE);
    log.viewMessage(message);
}

void PlayerObserver::changedHealth(int health) {
    std::string str;
    str = "[player_state]Player's health changed. Now there are " + std::to_string(health) + " health.";
    Message message = Message(str, Level::TRACE);
    log.viewMessage(message);
}

void PlayerObserver::playerWon() {
    Message message = Message("[player_state]Player won!", Level::TRACE);
    log.viewMessage(message);
}

void PlayerObserver::playerLost() {
    Message message = Message("[player_state]Player lost!", Level::TRACE);
    log.viewMessage(message);
}

PlayerObserver::PlayerObserver(Log &log_) {
     log = log_;
}
