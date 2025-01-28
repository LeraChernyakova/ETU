#include "FileLog.h"


FileLog::FileLog(const std::string& name) {
    file.open(name, std::ios_base::out | std::ios_base::app);
}

void FileLog::print(const Message& msg) {
    if (file.is_open())
        file << msg;
}

FileLog::~FileLog() {
    file.close();
}

