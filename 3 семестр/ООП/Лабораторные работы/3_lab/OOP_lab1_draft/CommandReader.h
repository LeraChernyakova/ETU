
#ifndef OOP_LAB1_COMMANDREADER_H
#define OOP_LAB1_COMMANDREADER_H

#include "Objects/Player.h"
#include "Direction.h"

class CommandReader {
public:
    Direction getDirection();
    int getFieldHeight();
    int getFieldWidth();
    int getLevel();
    bool getIsFileLogger();
    bool getIsConsoleLogger();
    bool getIsTraceLevel();
    bool getIsInfoLevel();
    bool getIsErrorLevel();
};


#endif //OOP_LAB1_COMMANDREADER_H
