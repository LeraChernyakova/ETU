
#ifndef OOP_LAB1_EXITFACTORY_H
#define OOP_LAB1_EXITFACTORY_H

#include "Factory.h"

class ExitFactory : public Factory{
public:
    Event* createEvent() final;
};


#endif //OOP_LAB1_EXITFACTORY_H

