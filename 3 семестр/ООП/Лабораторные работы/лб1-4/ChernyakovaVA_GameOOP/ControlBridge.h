#pragma once

class Player;
class MediatorObject;
class IMediator;
#include "Player.h"
#include "IControler.h"
#include "MediatorObject.h"

class ControlBridge : public MediatorObject {
private:
    std::map<char, Player::Moves> command_interpretator;
    IControler* controler;
    Player::Moves step;
public:
    ControlBridge(std::map<char, Player::Moves> maps, IControler* contrl);
    void next_step();
    Player::Moves get_step();
    ~ControlBridge();
};
