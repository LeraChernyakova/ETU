#include "ControlBridge.h"

#include <utility>

ControlBridge::ControlBridge(std::map<char, Player::Moves> maps, IControler* contrl) {
    command_interpretator = std::move(maps);
    controler = contrl;
    step = Player::NOTHING;
}

void ControlBridge::next_step() {
    char ch = controler->get_command();
    if (command_interpretator.count(ch) == 0) {
        step = Player::Moves::NOTHING;
    }
    else {
        step = command_interpretator.at(ch);
    }
    mediator->notify(this, IMediator::MEVENTS::STEP);
}

Player::Moves ControlBridge::get_step() {
    return step;
}

ControlBridge::~ControlBridge() {
    delete controler;
}