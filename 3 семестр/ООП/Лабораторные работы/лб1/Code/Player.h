#pragma once
#include <iostream>

class Player{
private:
	int health;
	int food;
	int resource;
public:
	Player();
	Player(int health, int food, int resource);
	//~Player();// 

	void setHealth(int food_);
	int getHealth();

	void setFood(int health_);
	int getFood();

	void setResource(int resource_);
	int getResource();

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
};