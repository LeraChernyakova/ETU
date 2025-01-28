
#ifndef OOP_LAB1_FOODFACTORY_H
#define OOP_LAB1_FOODFACTORY_H

#include "Factory.h"

class FoodFactory : public Factory{
public:
    Event* createEvent() final;
};


#endif //OOP_LAB1_FOODFACTORY_H
