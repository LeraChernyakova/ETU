
#ifndef OOP_LAB1_IEVENTOBSERVER_H
#define OOP_LAB1_IEVENTOBSERVER_H

#include "../Log.h"

class IEventObserver {
public:
    virtual void enemyAction(Log &log) = 0;
    virtual void trapAction(Log &log) = 0;
    virtual void foodAction(Log &log) = 0;
    virtual void moneyAction(Log &log) = 0;
    virtual void exitAction(Log &log) = 0;
    virtual ~IEventObserver() = default;
};


#endif //OOP_LAB1_IEVENTOBSERVER_H
