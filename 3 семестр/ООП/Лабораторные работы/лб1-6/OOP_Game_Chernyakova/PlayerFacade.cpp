#include "PlayerFacade.h"

PlayerFacade::PlayerFacade(FieldFacade* field) {
    this->field = field;
    this->player = new Player();
    this->controller = new PlayerController(this);
}
PlayerController& PlayerFacade::getController() {
    return *controller;
}
Player& PlayerFacade::getPlayer() {
    return *player;
}
FieldFacade& PlayerFacade::getFieldFacade() {
    return *field;
}
PlayerFacade::~PlayerFacade() {
    delete player;
    delete controller;
}