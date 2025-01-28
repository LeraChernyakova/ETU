#include "FactoryExit.h"

IEvent* FactoryExit::createEvent() {
    return new Exit;
}
