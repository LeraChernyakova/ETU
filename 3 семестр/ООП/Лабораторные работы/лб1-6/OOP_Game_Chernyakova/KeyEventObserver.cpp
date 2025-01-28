#include "KeyEventObserver.h"

void KeyEventObserver::onKeyEventInvoked() {
    Logger::getInstance() << LogMessage{ "The player got the key", Logger::Trace };
}