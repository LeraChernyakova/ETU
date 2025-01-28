
#include "CommandReader.h"
#include <iostream>
#include <conio.h>

int CommandReader::getFieldHeight() {
    int height;
    std::cout << "Enter field height:";
    std::cin >> height;
    return height;
}

int CommandReader::getFieldWidth() {
    int width;
    std::cout << "Enter field width:";
    std::cin >> width;
    return width;
}

Direction CommandReader::getDirection() {
    char op = 'l';
    op = getch();

    switch (op) {
        case 'w':
        case 'W':
            return Direction::UP;
        case 's':
        case 'S':
            return Direction::DOWN;
        case 'a':
        case 'A':
            return Direction::LEFT;
        case 'd':
        case 'D':
            return Direction::RIGHT;
        case 't':
        case 'T':
            return Direction::DOUBLE_UP;
        case 'g':
        case 'G':
            return Direction::DOUBLE_DOWN;
        case 'h':
        case 'H':
            return Direction::DOUBLE_RIGHT;
        case 'f':
        case 'F':
            return Direction::DOUBLE_LEFT;
        case 'e':
        case 'E':
            return Direction::EXIT;
        default:
            return Direction::NONE;
    }

}

int CommandReader::getLevel() {
    int level;
    std::cout << "Choose logging levels:\n";
    std::cout << "\t1. If you want to see all changes\n";
    std::cout << "\t2. If you want to see errors and game changes (is started/ended and etc.) \n";
    std::cout << "\t3. If you want to see only errors\n";
    std::cin >> level;
    return level;
}

bool CommandReader::getIsFileLogger() {
    std::cout << "Do you want to write changes in file? (y/n)\n";
    char answer;
    std::cin >> answer;
    if (answer == 'y')
        return true;
    return false;
}

bool CommandReader::getIsConsoleLogger() {
    std::cout << "Do you want to write changes in console? (y/n)\n";
    char answer;
    std::cin >> answer;
    if (answer == 'y')
        return true;
    return false;
}

bool CommandReader::getIsTraceLevel() {
    std::cout << "Do you want to log field and player changes? (y/n)\n";
    char answer;
    std::cin >> answer;
    if (answer == 'y')
        return true;
    return false;
}

bool CommandReader::getIsInfoLevel() {
    std::cout << "Do you want to log game changes? (y/n)\n";
    char answer;
    std::cin >> answer;
    if (answer == 'y')
        return true;
    return false;
}

bool CommandReader::getIsErrorLevel() {
    std::cout << "Do you want to log errors? (y/n)\n";
    char answer;
    std::cin >> answer;
    if (answer == 'y')
        return true;
    return false;
}



