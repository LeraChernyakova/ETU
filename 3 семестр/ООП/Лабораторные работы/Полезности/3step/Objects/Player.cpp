#include "Player.h"

Player::~Player(){
    delete[] ability;
    delete[] event;
};

Player::Player( int strength, int health, int bill, int exit, int hole, int exitP){
    ability=new PlayerAbilities(strength, health, bill);
    event= new PlayerEvents(exit, hole, exitP);
}

void Player::increaseBill(int sum){
    ability->increaseBill(sum);
}

void Player::changeExitP(){
    event->changeExitP();
}
int Player::getExitP(){
    return event->getExitP();
};

void Player::increaseHole(){
    event->increaseHole(1);
};

void Player::downHole(){
    event->increaseHole(0);
};

int Player::getHole(){
    return event->getHole();
}

int Player::getBill(){
    ability->getBill();
}

void Player::deadMan(){
    ability->deadMan();
};

void Player::increaseStrength(){
    ability->increaseStrength();
};

int Player::getStrength(){
   ability->getStrength();
};

int Player::getExit(){
    return event->getExit();
};

int Player::increaseExit(){
    event->increaseExit(1);
};

void Player::increaseHealth(int sum){
    ability->increaseHealth(sum);
}

int Player::getHP(){
    ability->getHP();
}