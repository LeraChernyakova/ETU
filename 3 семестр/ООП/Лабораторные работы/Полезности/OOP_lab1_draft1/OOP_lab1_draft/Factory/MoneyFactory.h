
#ifndef OOP_LAB1_MONEYFACTORY_H
#define OOP_LAB1_MONEYFACTORY_H

#include "Factory.h"

class MoneyFactory : public Factory{
public:
    Event* createEvent() final;
};


#endif //OOP_LAB1_MONEYFACTORY_H
