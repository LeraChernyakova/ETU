#include "Cave.h"

void Cave::addGood(Player& player) {
    player.addHealth(2);
    player.addFood(1);
}

void Cave::reaction(Player& player) {
    this->addGood(player);
    this->addPlayerScore(player);
}
