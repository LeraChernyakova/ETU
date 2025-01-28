
#ifndef OOP_LAB1_IPLAYEROBSERVER_H
#define OOP_LAB1_IPLAYEROBSERVER_H

#include "../Log.h"

class IPlayerObserver {
public:
    virtual void changedPoints(Log &log, int points) = 0;
    virtual void changedProtection(Log &log, int protection) = 0;
    virtual void changedHealth(Log &log, int health) = 0;
    virtual void playerWon(Log &log) = 0;
    virtual void playerLost(Log &log) = 0;
    virtual ~IPlayerObserver() = default;
};


#endif //OOP_LAB1_IPLAYEROBSERVER_H
