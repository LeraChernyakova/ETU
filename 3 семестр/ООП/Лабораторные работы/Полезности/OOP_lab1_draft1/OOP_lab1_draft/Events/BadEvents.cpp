
#include "BadEvents.h"

void BadEvents::remPoints(Player &player, Log &log) {
    player.remPlayerPoints(5, log);
}
