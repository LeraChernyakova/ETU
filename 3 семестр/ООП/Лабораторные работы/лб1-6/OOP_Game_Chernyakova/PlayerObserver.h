#pragma once

#include "IPlayerObserver.h"
#include "Player.h"
#include "GameObserver.h"

class PlayerObserver : public IPlayerObserver {
public:
    explicit PlayerObserver(GameObserver* observer);
    void HealthChanged(int value) override;
    void ProtectChanged(int value) override;
    void HasKeyToWin() override;
    void win()override;
    //IPlayerObserver& operator<<(const Player& player)override;
private:
    GameObserver* observer;
};
