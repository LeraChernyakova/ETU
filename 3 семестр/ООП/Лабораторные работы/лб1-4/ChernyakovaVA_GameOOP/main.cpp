#include "Game.h"
#include "IOCommander.h"
#include "Mediator.h"
#include "LogPool.h"
#include "Message.h"
#include "FileLog.h"

int main() {
    Game game;
    IOCommander commander;
    Mediator mediator(&game, &commander);
    game.start();
}