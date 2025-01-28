
#ifndef OOP_LAB1_FIELDOBSERVER_H
#define OOP_LAB1_FIELDOBSERVER_H

#include "IFieldObserver.h"

class FieldObserver : public IFieldObserver{
public:
    void openExit(Log &log) final;
    void changedPlayerPosition(Log &log, int x_position, int y_position) final;
    void stepOnBarrier(Log &log) final;
};


#endif //OOP_LAB1_FIELDOBSERVER_H
