#pragma once

class Player;
class IPlayerObserver {
public:
    virtual void HealthChanged(int value) = 0;
    virtual void ProtectChanged(int value) = 0;
    virtual void HasKeyToWin() = 0;
    virtual void win() = 0;
    //  virtual IPlayerObserver& operator<<(const Player& player) = 0;
};