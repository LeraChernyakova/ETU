#pragma once
#include "Factory.h"
#include "../Advantages/Exit.h"

class ExitFactory: public Factory{
public:
    Event* createEvent() final;
};
