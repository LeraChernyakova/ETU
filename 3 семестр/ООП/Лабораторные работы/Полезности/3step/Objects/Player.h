#pragma once
#include "../Objects/PlayerAbilities.h"
#include "../Objects/PlayerEvents.h"

class Player {
        PlayerAbilities* ability;
        PlayerEvents* event;
    public:
        explicit Player(int strength=1, int health=5, int bill=50, int exit=0, int hole=0, int exitP=0);

        ~Player();

        void increaseBill(int sum);

        void increaseHealth(int sum);

        void increaseHole();

        int getHole();

        void changeExitP();

        int getExitP();

        int getBill();

        void downHole();

        int getExit();

        int increaseExit();

        void deadMan();

        int getStrength();

        void increaseStrength();
        int getHP();
};

