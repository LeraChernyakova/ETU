
#ifndef OOP_LAB1_TRAPFACTORY_H
#define OOP_LAB1_TRAPFACTORY_H

#include "Factory.h"

class TrapFactory : public Factory {
public:
    Event *createEvent() final;
};


#endif //OOP_LAB1_TRAPFACTORY_H
