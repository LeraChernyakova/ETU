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
    op = _getch();
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
    case 'e':
    case 'E':
        return Direction::EXIT;
    default:
        return Direction::NONE;
    }

}



