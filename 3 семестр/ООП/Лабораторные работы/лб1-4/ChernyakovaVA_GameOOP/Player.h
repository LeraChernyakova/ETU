#pragma once

#include "ISubject.h"
#include "MessageFactory.h"
#include <vector>
#include <algorithm>
#include <cstdio>

class Player : public ISubject {
private:
    int hearts;
    int power;
    int max_stat;
    int coins;
    std::vector<IObserver*> observers;
public:
    enum Moves {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        EXIT,
        MENU,
        NOTHING
    };
    explicit Player(int hearts = 3, int power = 3);
    ~Player() = default;
    int get_hearts() const;
    int get_coins() const;
    int get_power() const;
    int get_max_stat() const;
    void set_hearts(int heart);
    void set_power(int dmg);
    void set_coins(int coin);
    void set_max_stat(int max);
};