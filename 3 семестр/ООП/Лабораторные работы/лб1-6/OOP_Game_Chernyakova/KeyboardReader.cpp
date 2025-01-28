#include <iostream>
#include "KeyboardReader.h"
#include <windows.h>
void KeyboardReader::readCommand() {
    for (const auto& pair : scheme.scheme) {
        if (GetAsyncKeyState(pair.first) & 0x8000) {
            mediator->process(InputMessage{ pair.second });
        }
    }
}
void KeyboardReader::setScheme(const ControlScheme& scheme) {
    this->scheme = scheme;
}
KeyboardReader::KeyboardReader(IInputMediator* mediator) : InputReader(mediator) {}