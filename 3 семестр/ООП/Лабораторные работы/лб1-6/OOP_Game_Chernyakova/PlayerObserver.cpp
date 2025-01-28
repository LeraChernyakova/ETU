#include "PlayerObserver.h"
#include "Logger.h"
#include <iostream>
#include "Player.h"

PlayerObserver::PlayerObserver(GameObserver* observer) : observer(observer) {}

void PlayerObserver::HealthChanged(int value) {
    Logger::getInstance() << LogMessage{
        "Health changed to " + std::to_string(value), Logger::Trace };
    if (value <= 0) {
        std::cout << "You died:(\n";
        observer->stop();
    }
}

void PlayerObserver::win() {
    std::cout << "You win:)\n";
    observer->stop();
}
void PlayerObserver::ProtectChanged(int value) {
    Logger::getInstance() << LogMessage{
        "Protect changed to " + std::to_string(value), Logger::Trace };
}
void PlayerObserver::HasKeyToWin() {
    Logger::getInstance() << LogMessage{ "The player has the key to the door to win  ", Logger::Trace };
}
//IPlayerObserver& PlayerObserver::operator<<(const Player& player) {
//    std::cout << "Count of lives = " << player.getLives() << std::endl;
//    std::cout << "Degree of protection = " << player.getProtection() << std::endl;
//    return *this;
//}