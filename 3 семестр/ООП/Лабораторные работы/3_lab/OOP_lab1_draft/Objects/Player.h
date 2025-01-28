
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

    void addPlayerPoints(int num);
    void addPlayerHealth(int num);
    void addPlayerProtection(int num);

    void remPlayerPoints(int num);
    void remPlayerHealth(int num);
    void remPlayerProtection(int num);
    void setWin();
    void setDead();
    void setOpenExit();

    void setObserver(Log &log);
};

#endif //OOP_LAB1_PLAYER_H
