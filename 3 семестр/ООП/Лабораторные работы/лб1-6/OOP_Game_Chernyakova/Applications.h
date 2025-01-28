#pragma once

#include "FieldFacade.h"
#include "PlayerFacade.h"
#include "EventObserverPool.h"
#include "PrintField.h"
#include "SaveController.h"
#include "GameController.h"
#include "InputMediator.h"
#include "FieldObserver.h"
#include "PlayerObserver.h"
#include "ControllerObserver.h"

class Applications {
public:
    Applications();
    void start();
    void stop();
    void save();
    void load();
private:
    bool playing_flag;
    PrintField pf;
    FieldFacade* field;
    PlayerFacade* player;
    GameController game_controller;
    SaveController controller;
    InputMediator mediator;
    ControllerObserver cont_observer;
    GameObserver game_observer;
    FieldObserver field_observer;
    PlayerObserver player_observer;
};