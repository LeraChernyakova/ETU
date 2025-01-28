#pragma once

#include "Field.h"
template <class ... Rules>
class FieldGen {
public:
    Field* execute(Player* player) {
        auto* field = new Field;
        field->set_player(player);
        (Rules()(field), ...);
        return field;
    };
};