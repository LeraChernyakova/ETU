#pragma once

#include <fstream>
#include "ILogger.h"


class FileLogger : public ILogger{
private:
    std::ofstream file;
public:
    FileLogger();
    explicit FileLogger(const std::string& filename);
    ILogger &operator <<(Message message) final;
    ~FileLogger() override;
};

