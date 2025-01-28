
#ifndef OOP_LAB1_PLAYEROBSERVER_H
#define OOP_LAB1_PLAYEROBSERVER_H

#include "IPlayerObserver.h"

class PlayerObserver : public IPlayerObserver{
private:
    Log log;
public:
    explicit PlayerObserver(Log &log_);
    void changedPoints(int points) final;
    void changedProtection(int protection) final;
    void changedHealth(int health) final;
    void playerWon() final;
    void playerLost() final;
};


#endif //OOP_LAB1_PLAYEROBSERVER_H
