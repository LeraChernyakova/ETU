#pragma once
#include "../Control/Event.h"

class Factory {
public:
    virtual Event* createEvent()=0;//виртуальная функция
    virtual ~Factory() { };//вирт деструктор
};


