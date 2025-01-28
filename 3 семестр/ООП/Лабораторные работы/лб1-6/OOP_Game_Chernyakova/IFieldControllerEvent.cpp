#include "IFieldControllerEvent.h"


IFieldControllerEvent::IFieldControllerEvent(PlayerController* controller, Field* field) {
    this->field = field;
    this->controller = controller;
}