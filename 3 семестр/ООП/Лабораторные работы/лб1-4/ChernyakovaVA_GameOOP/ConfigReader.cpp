#include "ConfigReader.h"


std::map<char, Player::Moves>& ConfigReader::read_cfg() {
    std::cout << "Input config file name [.txt extension]:";
    std::string filename;
    std::cin >> filename;
    FileConfig cfg(filename);
    for (auto& pair : cfg.get_config()) {
        controls.insert(pair.second);
    }
    return controls;
}