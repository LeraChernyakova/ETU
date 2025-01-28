#include <iostream>
#include "GameObserver.h"
#include "Applications.h"

GameObserver::GameObserver(Applications* application) : application(application) {}
void GameObserver::stop() {
    application->stop();
}