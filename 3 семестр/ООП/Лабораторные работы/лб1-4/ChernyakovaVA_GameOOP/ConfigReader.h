#pragma once

#include "FileConfig.h"

class ConfigReader {
private:
    std::map<char, Player::Moves> controls;
public:
    ConfigReader() = default;
    std::map<char, Player::Moves>& read_cfg();
    ~ConfigReader() = default;
};
