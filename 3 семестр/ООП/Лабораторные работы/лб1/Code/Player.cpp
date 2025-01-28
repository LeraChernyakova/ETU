#include "Player.h"

Player::Player(){}
Player::Player(int health = 10, int food = 10, int resource = 0) : food(food), health(health), resource(resource) {}

void Player::setHealth(int health_) {
	health = health_;
}
int Player::getHealth() {
	return health;
}

void Player::setFood(int food_) {
	food = food_;
}
int Player::getFood() {
	return food;
}

void Player::setResource(int resource_) {
	resource = resource_;
}
int Player::getResource() {
	return resource;
}

void Player::moveDown() {
	//y--;
}
void  Player::moveUp() {
	//y++;
}
void  Player::moveLeft() {
	//x--;

}
void  Player::moveRight() {
	//x++;
}