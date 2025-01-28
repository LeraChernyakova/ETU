#include "Union.h"

Union::Union(bool level1, bool level2, bool level3, bool file, bool console, int y, Observable* observable){
    mas[0]= new FirstLevel(observable);
    mas[1]=new SecondLevel(observable);
    mas[2]=new ThirdLevel(observable);
    info=MessageInfo(level1, level2, level3, file, console, y);
    if (file && !info.getFile()) mas[2]->react1("[ProgramState] File not created", info, log, 0);
};

MessageInfo Union::getinfo(){
    return info;
};

LevelInterface* Union::getSecondLevel(){
    return mas[1];
};

LevelInterface* Union::getThirdLevel(){
    return mas[2];
};
LevelInterface* Union::getFirstLevel(){
    return mas[0];
};

Logger* Union::getLog(){
    return log;
};