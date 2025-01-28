#include "Defeat.h"

void Defeat::damage(Player& player){
    player.deadMan();
}

void Defeat::react(Player& player, Union union1){
    union1.getSecondLevel()->react1("Defeat", union1.getinfo(), union1.getLog(),0);
    damage(player);
};