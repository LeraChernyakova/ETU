#pragma once
#include "Player.h"

class IEvent {
public:
    virtual void reaction(Player& player) = 0;// = 0 ��������, ��� ������� "����� �����������"
    virtual ~IEvent() {};
};
