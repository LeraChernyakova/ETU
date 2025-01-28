#include "HealEvent.h"

HealEvent::HealEvent(Player* pl) {
    player = pl;
}

void HealEvent::execute() {
    if (player->get_hearts() < player->get_max_stat()) {
        player->set_hearts(player->get_max_stat());
    }
    if (player->get_power() < player->get_max_stat()) {
        player->set_power(player->get_max_stat());
    }
}