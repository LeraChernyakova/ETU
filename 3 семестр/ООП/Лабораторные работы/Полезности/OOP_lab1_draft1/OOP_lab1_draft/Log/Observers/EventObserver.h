
#ifndef OOP_LAB1_EVENTOBSERVER_H
#define OOP_LAB1_EVENTOBSERVER_H

#include "IEventObserver.h"

class EventObserver : public IEventObserver{
private:
    bool isActive;
public:
    void enemyAction(Log &log) final;
    void trapAction(Log &log) final;
    void foodAction(Log &log) final;
    void moneyAction(Log &log) final;
    void exitAction(Log &log) final;
};


#endif //OOP_LAB1_EVENTOBSERVER_H
