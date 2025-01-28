
#ifndef OOP_LAB1_ENEMY_H
#define OOP_LAB1_ENEMY_H

#include "BadEvents.h"
#include "../Log/Observers/EventObserver.h"


class Enemy : public BadEvents {
private:
    IEventObserver *event_observer;
public:
    Enemy();
    void playerReact(Player& player, Log &log) final;//�� ��������� � ������������ � eventa ���������
    void remBad(Player& player, Log &log) final;//log �� ��������
    ~Enemy() final;
};


#endif //OOP_LAB1_ENEMY_H
