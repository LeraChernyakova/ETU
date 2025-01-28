
#include "ExitFactory.h"

Event *ExitFactory::createEvent() {
    return new Exit;
}

