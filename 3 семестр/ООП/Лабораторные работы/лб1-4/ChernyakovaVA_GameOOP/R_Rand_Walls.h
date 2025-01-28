#pragma once

#include "Field.h"
#include "RNGenerator.h"

template<int count = 0>
class R_Rand_Walls {
public:
    void operator()(Field* field) {
        RNGenerator gen;
        std::uniform_int_distribution<int> dist_height{ 0, field->get_height() - 1 };
        std::uniform_int_distribution<int> dist_width{ 0, field->get_width() - 1 };

        int counter = 0;
        int real_count = new_count(count, field->get_count_free());

        while (counter < real_count) {
            int x = gen.get_random_value<int>(dist_width);
            int y = gen.get_random_value<int>(dist_height);

            if (field->get_cell(x, y).is_wall())
                continue;
            if (field->get_cell(x, y).get_event() != nullptr)
                continue;
            if (std::make_pair(x, y) == field->get_position())
                continue;
            field->get_cell(x, y).set_wall(true);
            field->set_count(field->get_count_free() - 1);
            counter++;
        }
        field->check_way();
    };
};
