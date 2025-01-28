
#ifndef OOP_LAB1_FOOD_H
#define OOP_LAB1_FOOD_H

#include "GoodEvents.h"
#include "../Log/Observers/EventObserver.h"

class Food : public GoodEvents{
private:
    IEventObserver *event_observer;
public:
    Food();
    void playerReact(Player &player, Log &log) final;
    void addGood(Player& player, Log &log) final;
    ~Food() final;
};


#endif //OOP_LAB1_FOOD_H
