#include "Player.h"

Player::Player(int hearts, int power) : hearts(hearts), power(power), coins(0) {
    max_stat = std::max<int>(hearts, power);
}

int Player::get_hearts() const {
    return this->hearts;
}

int Player::get_coins() const {
    return this->coins;
}

int Player::get_power() const {
    return this->power;
}

int Player::get_max_stat() const {
    return this->max_stat;
}

void Player::set_hearts(int heart) {
    this->hearts = heart;
    notify();
    MessageFactory::get_instance().create_message(GameObjects, "The player's hearts has been changed.");
}

void Player::set_power(int dmg) {
    this->power = dmg;
    notify();
    MessageFactory::get_instance().create_message(GameObjects, "The player's power has been changed.");
}

void Player::set_coins(int coin) {
    this->coins = coin;
    notify();
    MessageFactory::get_instance().create_message(GameObjects, "The player's coins has been changed.");
}

void Player::set_max_stat(int max) {
    this->max_stat = max;
    notify();
    MessageFactory::get_instance().create_message(GameObjects, "The player received a buff.");
}
