#include "Hungry.h"

void Hungry::addBad(Player& player) {
    player.cutFood(2);
}

void Hungry::reaction(Player& player) {
    this->addBad(player);
    this->cutPlayerScore(player);
    player.setDead();
}
