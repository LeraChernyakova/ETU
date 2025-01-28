#include "PlayerEventGen.h"

Event* PlayerEventGen::generate() {
    std::uniform_int_distribution<int> distr_percent{ 0, 100 };
    std::uniform_int_distribution<int> coins{ 3, 7 };
    std::uniform_int_distribution<int> damage{ 1, std::max(field->get_player()->get_hearts() - 1, 2) };
    std::uniform_int_distribution<int> power{ 1, std::max(field->get_player()->get_power() - 1, 2) };
    std::uniform_int_distribution<int> buf{ 1, 2 };
    int num = generator.get_random_value<int>(distr_percent);

    if (num < 15) {
        return new PoisonTrap(field->get_player(), generator.get_random_value<int>(damage));
    }
    else if (num < 30) {
        return new FrozenTrap(field->get_player(), generator.get_random_value<int>(power));
    }
    else if (num < 50) {
        return new HealEvent(field->get_player());
    }
    else if (num < 55) {
        return new Buff(field->get_player(), generator.get_random_value<int>(buf));
    }
    else {
        return new CoinEvent(field->get_player(), generator.get_random_value<int>(coins));
    }
}