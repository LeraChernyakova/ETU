#pragma once

#include "fstream"
#include "sstream"
#include "IConfig.h"

class FileConfig final : public IConfig {
private:
    std::fstream file;
    std::string used_chars;
    bool check_used(char ch);
public:
    explicit FileConfig(std::string& filename);
    std::map<std::string, std::pair<char, Player::Moves>> get_config() final;
    ~FileConfig() final;
};
