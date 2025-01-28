#include "PeacefulFactory.h"

Event* PeacefulFactory::createEvent() {
    return new Peaceful;
}