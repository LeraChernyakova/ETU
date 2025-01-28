
#ifndef OOP_LAB1_FACTORY_H
#define OOP_LAB1_FACTORY_H

#include "../Events/Enemy.h"
#include "../Events/Trap.h"
#include "../Events/Food.h"
#include "../Events/Money.h"
#include "../Events/Exit.h"

class Factory {
public:
    virtual Event *createEvent() = 0;
    virtual ~Factory() = default;
};


#endif //OOP_LAB1_FACTORY_H
