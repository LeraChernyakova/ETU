
#ifndef OOP_LAB1_TRAP_H
#define OOP_LAB1_TRAP_H

#include "BadEvents.h"
#include "../Log/Observers/EventObserver.h"

class Trap : public BadEvents {
private:
    IEventObserver *event_observer;
public:
    Trap();
    void playerReact(Player& player, Log &log) final;
    void remBad(Player& player, Log &log) final;
    ~Trap() final;
};


#endif //OOP_LAB1_TRAP_H
