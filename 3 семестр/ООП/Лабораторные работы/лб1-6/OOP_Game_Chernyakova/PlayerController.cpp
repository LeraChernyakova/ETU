#include "PlayerController.h"
#include <cmath>
#include "PlayerFacade.h"
#include "Logger.h"

PlayerController::PlayerController(PlayerFacade* player, int player_x, int player_y) {
    this->player = player;
    this->player_x = player_x;
    this->player_y = player_y;
    observer = nullptr;
}
Field& PlayerController::getField() {
    return player->getFieldFacade().getField();
}

int PlayerController::getPositionX() const {
    return player_x;
}
int PlayerController::getPositionY() const {
    return player_y;
}
bool PlayerController::setPosition(int new_position_x, int new_position_y) {
    if (getField().isPointPassable(new_position_x, new_position_y)) {
        getField().setCellActive(player_x, player_y, false);
        player_x = new_position_x;
        player_y = new_position_y;

        if (observer)
            observer->onPlayerPositionChanged(player_x, player_y);
        getField().setCellActive(player_x, player_y, true);
        getField().getCell(player_x, player_y).react();
        return true;
    }
    if (observer)
        observer->impassableCellWarning(new_position_x, new_position_y);
    return false;

}
void PlayerController::moveTo(int x, int y) {
    if (getField().isPointPassable(x, y)) {
        setPosition(x, y);

    }
}
void PlayerController::moveUp(int val) {
    val = (std::abs(val));
    setPosition(getPositionX(),
        (getPositionY() - val % getField().getHeight() + getField().getHeight()) % getField().getHeight());
}
void PlayerController::moveDown(int val) {
    val = std::abs(val);
    setPosition(getPositionX(), (getPositionY() + val) % getField().getHeight());
}

void PlayerController::moveLeft(int val) {
    val = std::abs(val);
    setPosition((getPositionX() - val % getField().getWidth() + getField().getWidth()) % getField().getWidth(),
        getPositionY());
}

void PlayerController::moveRight(int val) {
    val = std::abs(val);
    setPosition((getPositionX() + val) % getField().getWidth(), getPositionY());
}
void PlayerController::processCommand(const InputMessage& message) {
    switch (message.command) {
    case Command::move_up:moveUp();
        break;
    case Command::move_down:moveDown();
        break;
    case Command::move_left:moveLeft();
        break;
    case Command::move_right:moveRight();
        break;
    default:break;
    }
}
void PlayerController::setObserver(IControllerObserver* obs) {
    observer = obs;
}
