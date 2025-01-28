#include "LevelGenerator.h"

LevelGeneratorOutput LevelGenerator::makeField() {
    auto pair = LevelBuilder::make(generator->make());
    LevelGeneratorOutput out{ pair.first, pair.second };
    return out;
}
void LevelGenerator::setGenerator(IFieldGenerator* generator) {
    delete this->generator;
    this->generator = generator;
}
LevelGenerator::~LevelGenerator() {
    delete generator;
}