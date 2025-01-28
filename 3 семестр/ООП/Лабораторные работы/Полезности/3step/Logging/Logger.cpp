#include "Logger.h"

void Logger::update(MessageInfo info, std::string message){
    if (info.getFileT()){
        info.getFile()->operator<<(message);};
    if (info.getConsoleT()){
        info.getConsole()->operator<<(message);}
}