#pragma once
#include "../Control/Event.h"
#include "../Factory/Factory.h"
#include "../Factory/EnemyFactory.h"
#include "../Factory/MoneyFactory.h"
#include "../Factory/PeacefulFactory.h"
#include "../Factory/ExitFactory.h"
#include "../Factory/HoleFactory.h"

class Cell {
        Event* occasion=new Peaceful;
        bool active;
        bool barrier;
    public:
        explicit Cell(bool active=false, bool barrier=false);

        void changeEvent(bool event_type);

        Event* getOccasion();

        void setOccasion(Factory* factory);

        bool getBarrier();

        void setBarrier(bool obj);
};

