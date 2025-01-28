#include "PlayerAbilities.h"

PlayerAbilities::PlayerAbilities(int strength, int health, int bill): strength(strength), health(health), bill(bill){};

void PlayerAbilities::increaseBill(int sum){
    bill+=sum;
    if (bill<0)
        bill=0;
};

void PlayerAbilities::increaseHealth(int sum){
    health+=sum;
};

int PlayerAbilities::getBill(){
    return bill;
};

void PlayerAbilities::deadMan(){
    bill=0;
};

int PlayerAbilities::getStrength(){
    return strength;
};

void PlayerAbilities::increaseStrength(){
    strength+=1;
};

int PlayerAbilities::getHP(){
    return health;
};