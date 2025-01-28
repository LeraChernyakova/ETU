#pragma once

#include "SaveGame.h"
#include "Field.h"
#include "Player.h"
#include "PlayerController.h"
#include "FieldFacade.h"

class SaveController {
public:
    void save(const Field& field, const Player& player, const PlayerController& controller);
    std::pair<FieldFacade*, PlayerFacade*>load();
private:
    SaveGame saver{};

};