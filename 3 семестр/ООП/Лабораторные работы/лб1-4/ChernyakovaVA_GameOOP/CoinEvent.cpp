#include "CoinEvent.h"


CoinEvent::CoinEvent(Player* pl, int coin) {
    player = pl;
    coins = coin;
}

void CoinEvent::execute() {
    int coins_count = coins + player->get_coins();
    player->set_coins(coins_count);
}