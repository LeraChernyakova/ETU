#include "DoorEventObserver.h"

void DoorEventObserver::onDoorEventInvoked() {
    Logger::getInstance() << LogMessage{ "The player reached the door with the key", Logger::Trace };
}