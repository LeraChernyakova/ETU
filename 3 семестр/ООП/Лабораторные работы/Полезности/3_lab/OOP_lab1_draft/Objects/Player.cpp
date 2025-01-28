#include "Player.h"


Player::Player() : points(100), health(3), protection(100), win(false), dead(false), open_exit(false) {
    player_observer = nullptr;
}

int Player::getPoints() const {
    return this->points;
}

int Player::getHealth() const {
    return this->health;
}

int Player::getProtection() const {
    return this->protection;
}

bool Player::getWin() const{
    return this->win;
}

bool Player::getDead() const{
    return this->dead;
}

Player::~Player() {
    delete player_observer;
}

void Player::addPlayerPoints(int num){
    points += num;
    player_observer->changedPoints(points);
}

void Player::addPlayerHealth(int num){
    health += num;
    player_observer->changedHealth(health);
}

void Player::addPlayerProtection(int num){
    protection += num;
    player_observer->changedProtection(protection);
}

void Player::remPlayerPoints(int num){
    points -= num;
    player_observer->changedPoints(points);
}

void Player::remPlayerHealth(int num){
    health -= num;
    player_observer->changedHealth(health);
    if (health <= 0)
        this->setDead();
}

void Player::remPlayerProtection(int num){
    protection -= num;
    player_observer->changedProtection(protection);
    if (protection <= 0)
        this->setDead();
}

void Player::setWin() {
    this->win = true;
    player_observer->playerWon();
}

void Player::setDead() {
    this->dead = true;
    player_observer->playerLost();
}

bool Player::getOpenExit() const {
    return open_exit;
}

void Player::setOpenExit(){
    this->open_exit = true;
}

void Player::setObserver(Log &log) {
    player_observer = new PlayerObserver(log);
}
