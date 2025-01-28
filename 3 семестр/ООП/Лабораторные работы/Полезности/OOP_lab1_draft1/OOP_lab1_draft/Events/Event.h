
#ifndef OOP_LAB1_EVENT_H
#define OOP_LAB1_EVENT_H

#include "../Objects/Player.h"

class Event {
public:
    virtual void playerReact(Player& player, Log &log) = 0;
    virtual ~Event() = default;
};

#endif //OOP_LAB1_EVENT_H
