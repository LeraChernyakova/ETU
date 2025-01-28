#include "Player.h"


Player::Player() : points(100), health(3), protection(100), win(false), dead(false), open_exit(false) {
    player_observer = new PlayerObserver;
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

void Player::addPlayerPoints(int num, Log &log){
    points += num;
    player_observer->changedPoints(log, points);
}

void Player::addPlayerHealth(int num, Log &log){
    health += num;
    player_observer->changedHealth(log, health);
}

void Player::addPlayerProtection(int num, Log &log){
    protection += num;
    player_observer->changedProtection(log, protection);
}

void Player::remPlayerPoints(int num, Log &log){
    points -= num;
    player_observer->changedPoints(log, points);
}

void Player::remPlayerHealth(int num, Log &log){
    health -= num;
    player_observer->changedHealth(log, health);
    if (health <= 0)
        this->setDead(log);
}

void Player::remPlayerProtection(int num, Log &log){
    protection -= num;
    player_observer->changedProtection(log, protection);
    if (protection <= 0)
        this->setDead(log);
}

void Player::setWin(Log &log) {
    this->win = true;
    player_observer->playerWon(log);
}

void Player::setDead(Log &log) {
    this->dead = true;
    player_observer->playerLost(log);
}

bool Player::getOpenExit() const {
    return open_exit;
}

void Player::setOpenExit(){
    this->open_exit = true;
}
