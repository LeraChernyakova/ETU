#pragma once
#include "Observable.h"
#include "FirstLevel.h"
#include "SecondLevel.h"
#include "ThirdLevel.h"

class Union {
    MessageInfo info;
    LevelInterface* mas[3];
    Logger* log;
public:
    Union(bool level1, bool level2, bool level3, bool file, bool console, int y, Observable* observable);
    MessageInfo getinfo();
    LevelInterface* getFirstLevel();
    LevelInterface* getSecondLevel();
    LevelInterface* getThirdLevel();
    Logger* getLog();
};

