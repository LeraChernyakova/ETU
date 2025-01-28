#pragma once

#include "Util_Funcs.h"
#include "Field.h"

template<int row_index, int x_start = 0, int x_end = -1, bool with_force = false>
class R_Row_Walls {
public:
    void operator() (Field* field) {

        if (check_pos(row_index, field->get_height() - 1))
            return;
        if (check_pos(x_start, field->get_width() - 1))
            return;
        if (check_pos(x_end, field->get_width() - 1))
            return;

        if (x_start > x_end)
            return;
        for (int i = x_start; i < x_end; ++i) {
            if (std::make_pair(i, row_index) == field->get_position())
                continue;
            placer(field->get_cell(i, row_index), with_force);
            field->set_count(field->get_count_free() - 1);
        }
        field->check_way();
    }
};