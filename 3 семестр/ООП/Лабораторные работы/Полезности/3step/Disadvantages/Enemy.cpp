#include "Enemy.h"

void Enemy::damage(Player& player){
    if (player.getStrength()<3) player.increaseHealth(-1);
}

void Enemy::react(Player& player, Union union1) {
    if (player.getStrength()<3)
        union1.getFirstLevel()->react1("HP", union1.getinfo(), union1.getLog(), 1);
    union1.getFirstLevel()->react1("Enemy", union1.getinfo(), union1.getLog(),2);
    damage(player);
};