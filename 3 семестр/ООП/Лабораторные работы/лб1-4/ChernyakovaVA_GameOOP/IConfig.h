#pragma once

#include <map>
#include <utility>
#include <string>
#include "Player.h"

class IConfig {
protected:
    std::map<std::string, char> command_default{
            {"UP:", 'w'},
            {"DOWN:", 's'},
            {"LEFT:", 'a'},
            {"RIGHT:", 'd'},
            {"EXIT:", 'e'},
            {"MENU:", 'm'}
    };
    std::map<std::string, std::pair<char, Player::Moves>> commands{
            {"UP:", {{},Player::Moves::UP}},
            {"DOWN:", {{},Player::Moves::DOWN}},
            {"LEFT:", {{},Player::Moves::LEFT}},
            {"RIGHT:", {{},Player::Moves::RIGHT}},
            {"EXIT:", {{},Player::Moves::EXIT}},
            {"MENU:", {{},Player::Moves::MENU}}
    };
    void set_default();
    void is_ok();
public:
    virtual std::map<std::string, std::pair<char, Player::Moves>> get_config() = 0;
    virtual ~IConfig() = default;
};