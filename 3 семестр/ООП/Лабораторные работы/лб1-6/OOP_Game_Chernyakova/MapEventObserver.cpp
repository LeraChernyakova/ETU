#include "MapEventObserver.h"

void MapEventObserver::onMapEventInvoked() {
    Logger::getInstance() << LogMessage{ "The playing field is filled with water", Logger::Trace };
}