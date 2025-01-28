
#ifndef OOP_LAB1_GAMEOBSERVER_H
#define OOP_LAB1_GAMEOBSERVER_H

#include "IGameObserver.h"

class GameObserver : public IGameObserver{
public:
    void gameStarted(Log &log) final;
    void gameEnded(Log &log) final;
    void invalidFieldHeight(Log &log) final;
    void invalidFieldWidth(Log &log) final;
};


#endif //OOP_LAB1_GAMEOBSERVER_H
