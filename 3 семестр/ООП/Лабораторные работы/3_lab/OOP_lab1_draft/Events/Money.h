
#ifndef OOP_LAB1_MONEY_H
#define OOP_LAB1_MONEY_H

#include "GoodEvents.h"
#include "../Log/Observers/EventObserver.h"


class Money :public GoodEvents{
private:
    IEventObserver *event_observer;
public:
    Money();
    void playerReact(Player &player, Log &log) final;
    void addGood(Player &player, Log &log) final;
    ~Money() final;
};


#endif //OOP_LAB1_MONEY_H
