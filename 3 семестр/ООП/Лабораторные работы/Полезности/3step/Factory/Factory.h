#pragma once
#include "../Control/Event.h"

class Factory {
public:
    virtual Event* createEvent()=0;//����������� �������
    virtual ~Factory() { };//���� ����������
};


