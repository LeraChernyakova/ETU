#pragma once

class Game;
class IOCommander;

#include "Game.h"
#include "IOCommander.h"
#include "IMediator.h"
#include "MediatorObject.h"
#include "ControlBridge.h"
#include "ConfigReader.h"
#include "ConsoleControler.h"

class Mediator : public IMediator {
private:
    Game* game;
    IOCommander* commander;
    ControlBridge* control;
    LogPool* log;
    void game_handler(IMediator::MEVENTS cmd);
    void commander_handler(IMediator::MEVENTS cmd);
public:
    Mediator(Game* pGame, IOCommander* pCommander);
    void set_log(LogPool*) final;
    void notify(MediatorObject* who, IMediator::MEVENTS event) final;
    ~Mediator() override;

    void g_start();
};