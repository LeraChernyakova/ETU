#pragma once

#include <fstream>
#include "ILogger.h"
#include "Player.h"
#include "PlayerController.h"
#include "Field.h"
class FileLogger : public ILogger {
public:
    FileLogger();
    explicit FileLogger(const std::string& filename);
    ~FileLogger() override;
    ILogger& operator<<(const std::string& str) override;
    void setOffset(int offset) override;
private:
    std::ofstream file;
};