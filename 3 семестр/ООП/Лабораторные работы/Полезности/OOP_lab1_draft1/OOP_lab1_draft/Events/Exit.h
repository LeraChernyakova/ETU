
#ifndef OOP_LAB1_EXIT_H
#define OOP_LAB1_EXIT_H

#include "GoodEvents.h"
#include "../Log/Observers/EventObserver.h"

class Exit : public GoodEvents{
private:
    IEventObserver *event_observer;
public:
    Exit();
    void addGood(Player& player, Log &log) final;
    void playerReact(Player &player, Log &log) final;
    ~Exit() final;
};


#endif //OOP_LAB1_EXIT_H
