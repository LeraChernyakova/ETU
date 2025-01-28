#pragma once

#include "Field.h"
#include "TreasureEvent.h"
#include "Util_Funcs.h"

template<int x, int y>
class R_Win_Cell {
public:
    void operator() (Field* field) {
        if (check_pos(x, field->get_width() - 1))
            return;
        if (check_pos(y, field->get_height() - 1))
            return;
        if (std::make_pair(x, y) == field->get_position())
            return;
        std::pair<int, int> win_cell_pos = field->get_win_cell_position();
        int win_cell_x = win_cell_pos.second;
        int win_cell_y = win_cell_pos.first;
        field->get_cell(win_cell_x, win_cell_y).set_event(nullptr);
        field->get_cell(x, y).set_wall(false);
        field->get_cell(x, y).set_event(new TreasureEvent(field->get_player()));
        auto pair = std::make_pair<int, int>(x, y);
        field->set_win_cell_pos(pair);
        field->set_count(field->get_count_free() - 1);
        field->check_way();
    }
};