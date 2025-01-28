#include "IConfig.h"

void IConfig::set_default() {
    MessageFactory::get_instance().create_message(Errors, "Default controls enable!");
    for (auto& pair : commands){
        pair.second = std::make_pair(command_default.at(pair.first), pair.second.second);
    }
}

void IConfig::is_ok() {
    for (auto& pair : commands)
    {
        if (!pair.second.first) {
            set_default();
            break;
        }
    }
}