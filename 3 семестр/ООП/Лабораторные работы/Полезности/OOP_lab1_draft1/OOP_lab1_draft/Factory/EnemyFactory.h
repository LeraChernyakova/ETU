
#ifndef OOP_LAB1_ENEMYFACTORY_H
#define OOP_LAB1_ENEMYFACTORY_H

#include "Factory.h"

class EnemyFactory : public Factory {
public:
    Event *createEvent() final;
};


#endif //OOP_LAB1_ENEMYFACTORY_H
