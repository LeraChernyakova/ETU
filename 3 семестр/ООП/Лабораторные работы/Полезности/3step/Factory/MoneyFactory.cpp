#include "MoneyFactory.h"

Event* MoneyFactory::createEvent() {
    return new Money;
}

