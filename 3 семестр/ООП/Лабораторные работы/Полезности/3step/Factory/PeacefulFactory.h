#pragma once
#include "Factory.h"
#include "../Advantages/Peaceful.h"

class PeacefulFactory: public Factory{
public:
    Event* createEvent() final;
};