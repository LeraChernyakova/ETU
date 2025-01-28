
#ifndef OOP_LAB1_APPLICATION_H
#define OOP_LAB1_APPLICATION_H

#include "CommandReader.h"
#include "Controller.h"
#include "Log/Observers/GameObserver.h"



class Application {
private:
    bool game;
    IGameObserver* game_observer;
public:
    void start();
    Application();
    ~Application();
};


#endif //OOP_LAB1_APPLICATION_H
