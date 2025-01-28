#include "Money.h"

void Money::occasion(Player& player){
    player.increaseBill(20);
    player.increaseStrength();
}

void Money::react(Player& player, Union union1) {
    union1.getFirstLevel()->react1("Bill", union1.getinfo(), union1.getLog(),1);
    union1.getFirstLevel()->react1("Money", union1.getinfo(), union1.getLog(),2);
    union1.getFirstLevel()->react1("Strength", union1.getinfo(), union1.getLog(), 1);
    occasion(player);
};
