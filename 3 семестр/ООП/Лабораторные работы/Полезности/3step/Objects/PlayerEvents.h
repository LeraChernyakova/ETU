#pragma once

class PlayerEvents {
    int exit;
    int exitP;
    int hole;
    public:

        PlayerEvents(int exit, int hole, int exitP);

        int getExit();

        int increaseExit(int increase);

        void changeExitP();

        void increaseHole(int increase);

        int getHole();

        int getExitP();
};
