#pragma once

#include "Util_Funcs.h"
#include "Field.h"

template<int column_index, int y_start = 0, int y_end = -1, bool with_force = false>
class R_Column_Walls {
public:
    void operator() (Field* field) {

        if (check_pos(column_index, field->get_height() - 1))
            return;
        if (check_pos(y_start, field->get_width() - 1))
            return;
        if (check_pos(y_end, field->get_width() - 1))
            return;

        if (y_start > y_end)
            return;

        for (int i = y_start; i < y_end; ++i) {
            if (std::make_pair(column_index, i) == field->get_position())
                continue;
            placer(field->get_cell(column_index, i), with_force);
            field->set_count(field->get_count_free() - 1);
        }
        field->check_way();
    }
};