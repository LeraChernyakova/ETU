#include "LogInit.h"
#include <iostream>
#include "Logger.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"

void LogInit::start() {
    std::cout << "Enter logging level: Trace - 1, Info - 2 or Error - 3\n" << std::endl;
    char temp;
    std::cin >> temp;
    switch (temp) {
    case '1':Logger::getInstance().setLevel(Logger::Trace);
        break;
    case '2':Logger::getInstance().setLevel(Logger::Info);
        break;
    case '3':Logger::getInstance().setLevel(Logger::Error);
        break;
    default:std::cout << "Level 1 by default\n";
        Logger::getInstance().setLevel(Logger::Error);
        break;
    }
    std::cout << "Console - 1\nFile - 2\nConsole and File - 3\nNothing -4\n";
    std::cin >> temp;
    if (temp == '1') {
        auto CLog = new ConsoleLogger();
        Logger::getInstance().addLogger(CLog);
    }
    else if (temp == '2') {
        std::cout << "If you want enter file name write anything or write '1'\n";
        std::string flag;
        std::cin >> flag;
        if (flag != "1") {
            std::cout << "Enter file name\n";
            std::string f;
            std::cin >> f;
            auto FLog = new FileLogger(f);
            Logger::getInstance().addLogger(FLog);
        }
        else {
            auto FLog = new FileLogger();
            Logger::getInstance().addLogger(FLog);
        }

    }
    else if (temp == '3') {
        std::cout << "If you want enter file name write anything or write '1'\n";
        std::string flag;
        std::cin >> flag;
        if (flag != "1") {
            std::cout << "Enter file name\n";
            std::string f;
            std::cin >> f;
            auto FLog = new FileLogger(f);
            Logger::getInstance().addLogger(FLog);
        }
        else {
            auto FLog = new FileLogger();
            Logger::getInstance().addLogger(FLog);
        }
        auto CLog = new ConsoleLogger();
        Logger::getInstance().addLogger(CLog);
    }
}