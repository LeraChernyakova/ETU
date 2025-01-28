
#ifndef OOP_LAB1_IPLAYEROBSERVER_H
#define OOP_LAB1_IPLAYEROBSERVER_H

#include "../Log.h"

class IPlayerObserver {
public:
    virtual void changedPoints(int points) = 0;
    virtual void changedProtection(int protection) = 0;
    virtual void changedHealth(int health) = 0;
    virtual void playerWon() = 0;
    virtual void playerLost() = 0;
    virtual ~IPlayerObserver() = default;
};


#endif //OOP_LAB1_IPLAYEROBSERVER_H
