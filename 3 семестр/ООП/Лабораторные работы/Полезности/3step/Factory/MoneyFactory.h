#pragma once
#include "Factory.h"
#include "../Advantages/Money.h"

class MoneyFactory: public Factory{
public:
    Event* createEvent() final;
};
