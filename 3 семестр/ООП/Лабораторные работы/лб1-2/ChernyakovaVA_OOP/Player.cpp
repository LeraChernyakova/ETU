#include "Player.h"

Player::Player() : health(10), food(5), score(10), resource(0), winner(false), dead(false), open_exit(false) {}

Player::~Player() {}

int Player::getHealth() const {
    return this->health;
}

int Player::getFood() const {
    return this->food;
}

int Player::getScore() const {
    return this->score;
}

int Player::getResource() const {
    return this->resource;
}

bool Player::getWinner() const {
    return this->winner;
}

bool Player::getDead() const {
    return this->dead;
}

bool Player::getOpenExit() const {
    return open_exit;
}

void Player::addHealth(int health_) {
    health += health_;
}

void Player::addFood(int food_) {
    food += food_;
}

void Player::addScore(int score_) {
    score += score_;
}

void Player::addResource(int resource_) {
    resource += resource_;
}

void Player::cutHealth(int health_) {
    health -= health_;
}

void Player::cutFood(int food_) {
    food -= food_;
}

void Player::cutScore(int score_) {
    score -= score_;
}

void Player::setWinner() {
    if (this->resource = 5)
        this->winner = true;
}

void Player::setDead() {
    if (this->health <= 0 || this->food <= 0)
        this->dead = true;
}

void Player::setOpenExit() {
    this->open_exit = true;
}
