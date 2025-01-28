#include "Holl.h"

void Holl::damage(Player& player){
    player.increaseHole();
};

void Holl::react(Player& player, Union union1) {
    union1.getFirstLevel()->react1("Holl", union1.getinfo(), union1.getLog(),2);
    damage(player);
};

