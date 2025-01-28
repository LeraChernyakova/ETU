#include <iostream>
#include "ControllerObserver.h"
#include "Logger.h"
#include "PlayerController.h"

void ControllerObserver::onPlayerPositionChanged(int pos_x, int pos_y) {
    Logger::getInstance() << LogMessage{
        "Player coordinate x is " + std::to_string(pos_x) + ", player coordinate y is " + std::to_string(pos_y),
        Logger::Trace };
}

void ControllerObserver::impassableCellWarning(int pos_x, int pos_y) {
    Logger::getInstance() << LogMessage{ "Attempt to move to an impassable cell (" + std::to_string(pos_y) + "," +
        std::to_string(pos_x) + ")", Logger::Trace };
}