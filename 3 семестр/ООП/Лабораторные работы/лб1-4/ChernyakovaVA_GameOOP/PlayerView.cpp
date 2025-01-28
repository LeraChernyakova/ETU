#include "PlayerView.h"

void PlayerView::update() {
    write_player_stats();
}

void PlayerView::write_player_stats() {
    std::cout << "Player stats:" << '\n'
        << "\tHearts " << player->get_hearts() << '\n'
        << "\tPower " << player->get_power() << '\n'
        << "\tCoins " << player->get_coins() << '\n'
        << "\tMaximum value of characteristics " << player->get_max_stat() << "\n";
}

PlayerView::PlayerView(Player* pl) : player(pl) {
    player->attach(this);
}