
#ifndef OOP_LAB1_CELL_H
#define OOP_LAB1_CELL_H

#include "../Events/Event.h"
#include "../Factory/Factory.h"

class Cell {
private:
    int x, y;
    bool active;
    bool barrier;
    Event* event;
public:
    Cell(int x, int y, bool active, bool barrier);
    Cell(int x, int y);
    Cell();
    ~Cell();

    void activeReaction();
    int getX();
    int getY();
    bool getActive();
    void changeBarrier();
    bool getBarrier();
    Event* getEvent();
    void changeEvent(Event* new_event);
    void setGood();
};

#endif //OOP_LAB1_CELL_H
