
#ifndef OOP_LAB1_PLAYER_H
#define OOP_LAB1_PLAYER_H

#include "../Log/Observers/PlayerObserver.h"

class Player {
private:
    int points;
    int health;
    int protection;
    bool win;
    bool dead;
    bool open_exit;
    IPlayerObserver* player_observer;

public:
    Player();

    int getPoints() const;
    int getHealth() const;
    int getProtection() const;
    bool getDead() const;
    bool getWin() const;
    bool getOpenExit() const;
    ~Player();

    void addPlayerPoints(int num, Log &log);
    void addPlayerHealth(int num, Log &log);
    void addPlayerProtection(int num, Log &log);

    void remPlayerPoints(int num, Log &log);
    void remPlayerHealth(int num, Log &log);
    void remPlayerProtection(int num, Log &log);
    void setWin(Log &log);
    void setDead(Log &log);

    void setOpenExit();
};

#endif //OOP_LAB1_PLAYER_H
