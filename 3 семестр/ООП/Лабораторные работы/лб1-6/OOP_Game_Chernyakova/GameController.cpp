#include "GameController.h"
#include "Applications.h"
void GameController::processCommand(const InputMessage& message) {
    switch (message.command) {
    case Command::load:
        app.load();
        break;
    case Command::save:
        app.save();
        break;
    default:break;
    }
}
GameController::GameController(Applications& applications) : app(applications) {}