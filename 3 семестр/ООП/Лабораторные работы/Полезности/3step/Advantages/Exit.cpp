#include "Exit.h"

void Exit::occasion(Player& player) {
    player.increaseExit();
}

void Exit::react(Player& player, Union union1){
    union1.getFirstLevel()->react(union1.getinfo(), union1.getLog(),2);
    occasion(player);
};