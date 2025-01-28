#include "TreasureEvent.h"

TreasureEvent::TreasureEvent(Player* pl) {
    player = pl;
}

void TreasureEvent::execute() {
    player->set_coins(100);
}