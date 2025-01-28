#include "FactoryHungry.h"

IEvent* FactoryHungry::createEvent() {
    return new Hungry;
}
