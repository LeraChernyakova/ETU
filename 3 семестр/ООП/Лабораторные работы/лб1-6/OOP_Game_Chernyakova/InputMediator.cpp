#include "InputMediator.h"

void InputMediator::process(const InputMessage& message) {
    for (auto controller : controllers) {
        controller->processCommand(message);
    }
}
void InputMediator::tick() {
    readers->readCommand();
}
void InputMediator::addReader(InputReader* reader) {
    readers = reader;
}
void InputMediator::addController(IController* controller) {
    controllers.insert(controller);
}

void InputMediator::removeController(IController* controller) {
    controllers.erase(controller);
}