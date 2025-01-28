#pragma once

#include "IPlayerObserver.h"
//class IPlayerObserver;///////////////////////////////////////////////////////

class Player {
public:
    explicit Player();
    void changeLives(int value);
    void changeProtection(int value);
    void changeScore(int value);
    int getLives() const;
    int getProtection() const;
    int getScore() const;
    bool doorKey() const;
    void foundKey();
    void setObserver(IPlayerObserver* player_observer);
    void victory();

private:
    bool door_key;
    int number_of_lives;
    int protection;
    int score;
    IPlayerObserver* observer;
};
