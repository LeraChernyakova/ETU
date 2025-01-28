#pragma once

#include "ILogger.h"
#include <fstream>
#include "Message.h"

class FileLog final : public ILogger {
private:
    std::ofstream file;
public:
    explicit FileLog(const std::string& name = "log.txt");
    void print(const Message& msg) override;
    ~FileLog() final;
};
