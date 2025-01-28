#include "BadEvent.h"

void BadEvent::cutPlayerScore(Player& player) {
    player.cutScore(4);
}