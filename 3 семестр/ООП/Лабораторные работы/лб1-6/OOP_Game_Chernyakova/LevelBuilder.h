#pragma once

#include "Field.h"
#include "FieldScheme.h"
#include "PlayerController.h"
#include "Player.h"
#include "FieldFacade.h"
#include <unordered_map>

class LevelBuilder {
public:
    static std::pair<FieldFacade*, PlayerFacade*> make(const FieldScheme& scheme);
private:
    static void typeEvent(CellType type,
        int x, int y,
        Cell& cell,
        Player* player,
        PlayerController* controller,
        Field* field);
};
