#include <iostream>
#include "ConsoleLogger.h"
#include "PrintField.h"

ILogger& ConsoleLogger::operator<<(const std::string& str) {
    if (_count >= _max_offset) {
        _count = 0;
    }
    PrintField::setCursorposition(0, _offset + _count);
    std::cout << std::string(100, ' ');
    PrintField::setCursorposition(0, _offset + _count++);
    std::cout << str << std::endl;
    return *this;
}
void ConsoleLogger::setOffset(int offset) {
    _offset = offset;
}
