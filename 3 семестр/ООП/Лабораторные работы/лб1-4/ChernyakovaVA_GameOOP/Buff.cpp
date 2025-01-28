#include "Buff.h"


Buff::Buff(Player* pl, int value) {
    player = pl;
    power_up = value;
}

void Buff::execute() {
    player->set_max_stat(player->get_max_stat() + power_up);
}