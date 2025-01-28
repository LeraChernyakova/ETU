#include "SaveController.h"
#include "FieldRegister.h"
#include "Logger.h"
#include "LevelBuilder.h"
#include <stdexcept>
#include <iostream>
#include "PlayerFacade.h"

void SaveController::save(const Field& field, const Player& player, const PlayerController& controller) {
    PlayerInfo pi{
        player.doorKey(), player.getLives(), player.getProtection(),
        controller.getPositionX(),
        controller.getPositionY()
    };
    FieldScheme scheme{ std::move(FieldRegister::getScheme(field)) };
    GameInfo gi{ std::move(scheme), pi };
    try {
        saver.save(gi);
    }
    catch (const SaveException& er) {
        Logger::getInstance() << LogMessage{ er.what(), Logger::Error };
    }

}
std::pair<FieldFacade*, PlayerFacade*> SaveController::load() {
    GameInfo info;
    try {
        info = std::move(saver.load());
    }
    catch (const SaveException& er) {
        Logger::getInstance() << LogMessage{ er.what(), Logger::Error };
        auto info_opt = er.getInfo();
        if (!info_opt.has_value()) {
            return { nullptr, nullptr };
        }
        info = info_opt.value();
    }
    auto pair = LevelBuilder::make(info.fi);
    auto& player = pair.second->getPlayer();
    auto& player_info = info.pi;
    if (player_info.door_key) {
        player.foundKey();
    }
    player.changeLives(player_info.number_of_lives);
    player.changeProtection(player_info.protection);
    pair.second->getController().setPosition(player_info.player_x, player_info.player_y);
    return pair;
}