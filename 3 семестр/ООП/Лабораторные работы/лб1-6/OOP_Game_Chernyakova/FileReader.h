#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include "InputMessage.h"

class FileReader {
public:
    FileReader();
    explicit FileReader(const std::string& filename);
    ~FileReader();
    void readFile(const std::string& filename);
    void defaultCommand();
    void setCommand(char symb, std::string num);
    std::map<char, Command>& getScheme();
private:
    std::ifstream file;
    std::map <char, Command> scheme;
};