#pragma once

#include "Field.h"
#include "Cell.h"
#include "Util_Funcs.h"

template<int width = 10, int height = 10>
class R_Field_Size {
public:
    void operator() (Field* field) {
        if (check_pos(width, 25))
            return;
        if (check_pos(height, 25))
            return;

        std::vector<std::vector<Cell>> cells;
        for (int i = 0; i < height; ++i) {
            cells.emplace_back();
            for (int j = 0; j < width; ++j) {
                cells.at(i).emplace_back();
            }
        }
        field->set_field(cells);
    }
};