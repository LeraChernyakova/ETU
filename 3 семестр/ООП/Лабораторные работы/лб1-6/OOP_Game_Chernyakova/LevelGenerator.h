#pragma once

#include "IFieldGenerator.h"
#include "LevelBuilder.h"
#include "FieldFacade.h"

struct LevelGeneratorOutput {
    FieldFacade* field;
    PlayerFacade* player;
};
class LevelGenerator {
public:
    LevelGeneratorOutput makeField();
    void setGenerator(IFieldGenerator* generator);
    ~LevelGenerator();
private:
    IFieldGenerator* generator;
};