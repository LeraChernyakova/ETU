#pragma once
#include "Factory.h"
#include "../Disadvantages/Enemy.h"

class EnemyFactory: public Factory {
public:
    Event* createEvent() final;
};

