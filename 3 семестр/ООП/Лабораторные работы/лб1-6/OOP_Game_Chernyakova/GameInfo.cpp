#include "GameInfo.h"
#include "CellRegister.h"

PlayerInfo::operator std::string() const {
    return std::to_string(door_key) + " " + std::to_string(number_of_lives) + " " + std::to_string(protection) + " "
        + std::to_string(player_x) + " " + std::to_string(player_y);
}

GameInfo::operator std::string() const {
    return std::string(fi) + "*******" + '\n' + std::string(pi);
}