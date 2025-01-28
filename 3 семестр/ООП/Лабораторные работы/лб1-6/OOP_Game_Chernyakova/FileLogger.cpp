#include <iostream>
#include "FileLogger.h"

FileLogger::FileLogger() : FileLogger("addFile.log") {}

FileLogger::FileLogger(const std::string& filename) : file(filename) {}

ILogger& FileLogger::operator<<(const std::string& str) {
    file << str << std::endl;
    return *this;
}

FileLogger::~FileLogger() {
    file.close();
}
void FileLogger::setOffset(int offset) {}