#include "BombEventObserver.h"

void BombEventObserver::onBombEventInvoked() {
    Logger::getInstance() << LogMessage{ "The player stepped on the bomb", Logger::Trace };
}