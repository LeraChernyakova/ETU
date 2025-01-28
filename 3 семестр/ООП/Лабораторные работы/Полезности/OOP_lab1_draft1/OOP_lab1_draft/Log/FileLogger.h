
#ifndef OOP_LAB1_FILELOGGER_H
#define OOP_LAB1_FILELOGGER_H

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


#endif //OOP_LAB1_FILELOGGER_H
