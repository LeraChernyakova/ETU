
#include "TrapFactory.h"

Event *TrapFactory::createEvent() {
    return new Trap;
}
