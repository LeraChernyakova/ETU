#pragma once

#include <string>
#include <vector>
#include "Cell.h"
#include "FieldScheme.h"

struct PlayerInfo {
    bool door_key;
    int number_of_lives;
    int protection;
    int player_x;
    int player_y;
    explicit operator std::string() const;
};
struct GameInfo {
    FieldScheme fi;
    PlayerInfo pi;
    explicit operator std::string() const;
};