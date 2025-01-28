#include "Cell.h"

    Cell::Cell(bool active, bool barrier):active(active), barrier(barrier){};

    Event* Cell::getOccasion(){
        return occasion;
    };
    void Cell::changeEvent(bool event_type){
        active=event_type;
    }

    bool Cell::getBarrier(){
        return barrier;
    };
     void Cell::setBarrier(bool obj){
         barrier=obj;
     }
    void Cell::setOccasion(Factory* factory){
        delete occasion;
        occasion=factory->createEvent();
    };

