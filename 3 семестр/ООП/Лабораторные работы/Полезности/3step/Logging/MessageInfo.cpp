#include "MessageInfo.h"

bool MessageInfo::getLevel(int number){
    switch (number){
        case 1:
            return levels[0];
        case 2:
            return levels[1];
        case 3:
            return levels[2];
    }
}

MessageInfo::MessageInfo(bool level1, bool level2, bool level3, bool file, bool console, int y):file(file), console(console){
    levels[0] = level1;
    levels[1] = level2;
    levels[2] = level3;
    if (level1) {
        levels[1] = level1;
        levels[2] = level1;
    }
    else if (level2){
        levels[2] = level2;
    }
    if (file)
        fileOut = new FileObject;
    if (console)
        consoleOut = new Console(y);
};


Output* MessageInfo::getConsole(){
    return consoleOut;
}

bool MessageInfo::getConsoleT(){
    return console;
}

bool MessageInfo::getFileT(){
    return file;
}

Output* MessageInfo::getFile(){
    return fileOut;
}
