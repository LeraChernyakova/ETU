
#include "FoodFactory.h"

Event *FoodFactory::createEvent() {
    return new Food;
}
