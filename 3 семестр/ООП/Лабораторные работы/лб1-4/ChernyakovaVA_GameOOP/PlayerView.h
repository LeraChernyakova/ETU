#pragma once
#include "IObserver.h"
#include "Player.h"
#include <iostream>

class PlayerView : public IObserver {
private:
    void write_player_stats();
    Player* player;
public:
    PlayerView() = default;
    explicit PlayerView(Player* pl);
    void update() override;
    ~PlayerView() = default;
};