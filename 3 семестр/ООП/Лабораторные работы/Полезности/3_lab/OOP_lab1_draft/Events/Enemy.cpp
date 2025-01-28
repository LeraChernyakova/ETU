
#include "Enemy.h"

void Enemy::remBad(Player &player, Log &log) {
    player.remPlayerHealth(1);
}

void Enemy::playerReact(Player &player, Log &log) {
    event_observer->enemyAction(log);
    this->remBad(player, log);
    this->remPoints(player, log);
    if (player.getHealth() < 1 or player.getPoints() < 1 or player.getProtection() < 1)
        player.setDead();
}

Enemy::Enemy() {
    event_observer = new EventObserver;
}

Enemy::~Enemy() {
    delete event_observer;
}
