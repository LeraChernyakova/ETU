#include "Resource.h"

void Resource::addGood(Player& player) {
    player.addResource(3);
}

void Resource::reaction(Player& player) {
    this->addGood(player);
    this->addPlayerScore(player);
    if (player.getResource() > 5 && !player.getOpenExit())
        player.setOpenExit();
}
