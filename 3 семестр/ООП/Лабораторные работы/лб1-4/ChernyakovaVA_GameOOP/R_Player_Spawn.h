#pragma once

#include "Field.h"

template<int x, int y>
class R_Player_Spawn {
public:
    void operator()(Field* field) {
        if (x < 0 && x > field->get_width() - 1)
            return;
        if (y < 0 && y > field->get_height() - 1)
            return;
        field->get_cell(x, y).set_wall(false);
        field->get_cell(x, y).set_event(nullptr);
        auto pair = std::make_pair<int, int>(x, y);
        field->set_player_pos(pair);
        field->check_way();
    };
};