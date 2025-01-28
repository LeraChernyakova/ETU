#include "ConsoleControler.h"

char ConsoleControler::get_command() {
    std::cout << "Input next move: ";
    char ch;
    std::cin >> ch;
    return ch;
}