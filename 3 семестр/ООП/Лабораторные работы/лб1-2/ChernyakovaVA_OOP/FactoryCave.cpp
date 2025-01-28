#include "FactoryCave.h"

IEvent* FactoryCave::createEvent() {
    return new Cave;
}
