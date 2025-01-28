#pragma once

#include "Field.h"
#include "TreasureEvent.h"

template <class ... Rules>
class FieldGen {
public:
    Field* execute(Player* player, int level) {
        auto* field = new Field();
        if (level == 1) {
            std::vector<std::vector<Cell>> cells;
            for (int i = 0; i < 7; ++i) {
                cells.emplace_back();
                for (int j = 0; j < 7; ++j) {
                    cells.at(i).emplace_back();
                }
            }
            field->set_field(cells);
            auto pair = std::make_pair<int, int>(6, 6);
            field->set_win_cell_pos(pair);
            field->get_cell(6, 6).set_event(new TreasureEvent(player));
        }
        if (level == 2) {
            std::vector<std::vector<Cell>> cells;
            for (int i = 0; i < 20; ++i) {
                cells.emplace_back();
                for (int j = 0; j < 20; ++j) {
                    cells.at(i).emplace_back();
                }
            }
            field->set_field(cells);
            auto pair = std::make_pair<int, int>(6, 6);
            field->set_win_cell_pos(pair);
            field->get_cell(19, 19).set_event(new TreasureEvent(player));
        }
        field->set_player(player);
        field->check_way();
        (Rules()(field), ...);
        return field;
    };
};