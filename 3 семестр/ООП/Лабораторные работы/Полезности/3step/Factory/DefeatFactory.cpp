#include "DefeatFactory.h"

Event* DefeatFactory::createEvent() {
    return new Defeat;
}