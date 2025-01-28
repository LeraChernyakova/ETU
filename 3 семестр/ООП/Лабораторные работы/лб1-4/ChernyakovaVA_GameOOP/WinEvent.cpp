#include "WinEvent.h"

WinEvent::WinEvent(Game* gm) {
    game = gm;
}

void WinEvent::execute() {
    game->set_status(Game::WIN);
}