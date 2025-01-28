#include "Player.h"
#include "GameObserver.h"

Player::Player() {
    door_key = false;
    number_of_lives = 3;
    protection = 0;
    score = 0;
    observer = nullptr;
}
void Player::setObserver(IPlayerObserver* player_observer) {
    observer = player_observer;
}
void Player::changeLives(int value) {
    number_of_lives += value;
    if (observer)
        observer->HealthChanged(number_of_lives);
}
void Player::changeProtection(int value) {
    protection += value;
}
void Player::changeScore(int value) {
    score += value;
}
int Player::getLives() const {
    return number_of_lives;
}
int Player::getProtection() const {
    return protection;
}
int Player::getScore() const {
    return score;
}
bool Player::doorKey() const {
    return door_key;
}
void Player::foundKey() {
    door_key = true;
    if (observer)
        observer->HasKeyToWin();////////////////////////////////////////////
}
void Player::victory() {
    if (observer)
        observer->win();
}