#include "EnemyFactory.h"

Event* EnemyFactory::createEvent() {
    return new Enemy;
}
