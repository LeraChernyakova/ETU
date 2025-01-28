#pragma once
#include "Factory.h"
#include "../Disadvantages/Defeat.h"

class DefeatFactory: public Factory{
public:
    Event* createEvent() final;
};
