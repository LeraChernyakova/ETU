#pragma once

class PlayerAbilities {
    int strength;
    int health;
    int bill;
    public:
        PlayerAbilities(int strength, int health, int bill);

        void increaseBill(int sum);

        void increaseHealth(int sum);

        int getBill();

        void deadMan();

        int getStrength();

        void increaseStrength();

        int getHP();
};

