#include "FactoryResource.h"

IEvent* FactoryResource::createEvent() {
    return new Resource;
}
