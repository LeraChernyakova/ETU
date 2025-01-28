#include "FactoryClan.h"

IEvent* FactoryClan::createEvent() {
    return new Clan;
}
