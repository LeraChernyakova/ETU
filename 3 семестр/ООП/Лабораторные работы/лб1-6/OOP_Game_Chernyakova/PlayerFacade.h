#pragma once

#include "FieldFacade.h"
#include "PlayerController.h"
#include "Player.h"

class PlayerFacade {
public:
    explicit PlayerFacade(FieldFacade* field);
    ~PlayerFacade();
    PlayerController& getController();
    Player& getPlayer();
    FieldFacade& getFieldFacade();
private:
    FieldFacade* field;
    PlayerController* controller;
    Player* player;
};