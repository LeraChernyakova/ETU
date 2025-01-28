#pragma once

#include "IControler.h"
#include <iostream>

class ConsoleControler final : public IControler {
public:
    ConsoleControler() = default;
    char get_command() final;
    ~ConsoleControler() final = default;
};
