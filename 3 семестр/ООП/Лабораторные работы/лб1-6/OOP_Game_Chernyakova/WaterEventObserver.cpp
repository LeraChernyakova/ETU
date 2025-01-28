#include "WaterEventObserver.h"

void WaterEventObserver::onWaterEventInvoked() {
    Logger::getInstance() << LogMessage{ "The player replenished the supply of water", Logger::Trace };
}