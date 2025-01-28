#include "IOCommander.h"
#include "FileLog.h"

void IOCommander::read_level_num() {
    std::cout << "Enter the level number(must be an integer):";
    std::cin >> level_num;
    mediator->notify(this, IMediator::LEVEL);
}

int IOCommander::get_level() const {
    return level_num;
}

std::vector<Levels> IOCommander::read_levels() {
    std::vector<Levels> list = { GameObjects, Gamestatus, Errors };
    std::cout << "Logging the level of the Game Status?\n";
    if (get_approve())
        return list;
    std::remove(list.begin(), list.end(), Gamestatus);
    std::cout << "Logging the level of the Game Objects?\n";
    if (get_approve())
        return list;
    std::remove(list.begin(), list.end(), GameObjects);
    std::cout << "Logging the level of the Errors?\n";
    if (get_approve())
        return list;
    std::remove(list.begin(), list.end(), Errors);
    return list;
}

bool IOCommander::get_approve() const {
    char ch;
    std::cout << "[1 - yes]\n";
    std::cin >> ch;
    return ch == '1';
}

void IOCommander::Defeat() const {
    std::cout << R"(\\\\\!DEFEAT!/////)" << '\n';
    std::cout << "\tBRUH!" << '\n';
    MessageFactory::get_instance().create_message(Gamestatus, "The game ended in defeat.");
}

void IOCommander::Victory() const {
    std::cout << R"(\\\\\!VICTORY!/////)" << '\n';
    std::cout << "\tWOW!" << '\n';
    MessageFactory::get_instance().create_message(Gamestatus, "The game ended in victory.");
}

void IOCommander::create_logger() {
    std::cout << "Do you need logs?\n";
    if (!get_approve())
        return;

    auto* log = new LogPool(&MessageFactory::get_instance());

    std::cout << "Console log?\n";
    if (get_approve())
        log->add_logger<ConsoleLog>();

    std::cout << "File log?\n";
    if (get_approve()) {
        std::cout << "Enter filename:\n";
        std::string filename;
        std::cin >> filename;
        log->add_logger<FileLog>(filename);
    }

    std::vector<Levels> list_levels;
    log->set_log_levels(read_levels());
    mediator->set_log(log);
}