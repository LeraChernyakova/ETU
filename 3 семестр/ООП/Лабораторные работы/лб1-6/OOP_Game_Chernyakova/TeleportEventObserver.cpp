#include "TeleportEventObserver.h"

void TeleportEventObserver::onTeleportEventInvoked() {
    Logger::getInstance() << LogMessage{ "The player teleported to the point (0,0)", Logger::Trace };
}