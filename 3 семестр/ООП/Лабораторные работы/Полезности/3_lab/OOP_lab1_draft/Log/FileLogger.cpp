
#include "FileLogger.h"

FileLogger::FileLogger() : FileLogger("FileLogger.txt") {}

ILogger &FileLogger::operator<<(Message message) {
    file << message.getMessage() << '\n';
    return *this;
}

FileLogger::~FileLogger() {
    file.close();
}

FileLogger::FileLogger(const std::string &filename) : file(std::ofstream(filename)) {}


