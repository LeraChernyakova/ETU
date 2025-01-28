#include "MediatorObject.h"

MediatorObject::MediatorObject(IMediator* med) : mediator(med) {
}

void MediatorObject::set_mediator(IMediator* med) {
    this->mediator = med;
}