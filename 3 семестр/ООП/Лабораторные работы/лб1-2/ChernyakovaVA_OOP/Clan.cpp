#include "Clan.h"

void Clan::addBad(Player& player) {
    player.cutHealth(5);
    player.cutFood(3);
}

void Clan::reaction(Player& player) {
    this->addBad(player);
    this->cutPlayerScore(player);
    player.setDead();
}
