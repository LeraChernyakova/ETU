#pragma once

#include "Player.h"
#include "Direction.h"

class CommandReader {
public:
    Direction getDirection();
    int getFieldHeight();
    int getFieldWidth();
};
