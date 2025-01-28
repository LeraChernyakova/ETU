#pragma once
#include "Factory.h"
#include "../Disadvantages/Holl.h"

class HoleFactory: public Factory {
public:
    Event* createEvent() final;
};

