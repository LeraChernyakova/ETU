
#ifndef OOP_LAB1_PLAYEROBSERVER_H
#define OOP_LAB1_PLAYEROBSERVER_H

#include "IPlayerObserver.h"

class PlayerObserver : public IPlayerObserver{
public:
    void changedPoints(Log &log, int points) final;
    void changedProtection(Log &log, int protection) final;
    void changedHealth(Log &log, int health) final;
    void playerWon(Log &log) final;
    void playerLost(Log &log) final;
};


#endif //OOP_LAB1_PLAYEROBSERVER_H
