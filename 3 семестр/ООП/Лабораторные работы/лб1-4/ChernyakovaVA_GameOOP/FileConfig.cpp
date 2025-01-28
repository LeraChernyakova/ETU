#include "FileConfig.h"
#include <cstring>

FileConfig::FileConfig(std::string& filename) {
    file.open(filename, std::ios_base::in);
}

bool FileConfig::check_used(char ch) {
    for (char used_char : used_chars)
    {
        if (used_char == ch)
            return false;
    }
    return true;
}

std::map<std::string, std::pair<char, Player::Moves>> FileConfig::get_config() {
    if (!file.is_open()) {
        MessageFactory::get_instance().create_message(Errors, "CFG File isn't open!");
        set_default();
        return commands;
    }
    std::string line;
    while (getline(file, line))
    {
        std::string command;
        char button = '\0';
        std::string buttonstring;

        std::istringstream stream(line);
        stream >> command >> buttonstring;

        if (buttonstring.length() > 1) {
            MessageFactory::get_instance().create_message(Errors, "Command too long.");
            set_default();
            break;
        }

        if (buttonstring.length() == 1) {
            button = buttonstring[0];
        }

        if (commands.count(command) == 0) {
            MessageFactory::get_instance().create_message(Errors, "Incorrect command prefix.");
            set_default();
            break;
        }

        if (button == '\0') {
            MessageFactory::get_instance().create_message(Errors, "Button is not set for prefix.");
            set_default();
            break;
        }

        if (!check_used(button)) {
            MessageFactory::get_instance().create_message(Errors, "Control button is already busy.");
            set_default();
            break;
        }

        used_chars = used_chars + button;
        if (!commands.at(command).first) {
            commands.at(command).first = button;
        }
        else {
            MessageFactory::get_instance().create_message(Errors, "Two or more identical prefixes in the cfg file.");
            set_default();
            break;
        }
    }
    is_ok();
    return commands;
}

FileConfig::~FileConfig() {
    file.close();
}