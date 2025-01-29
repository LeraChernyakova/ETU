#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "../model/matrix.h"

void readMatricesFromFile(std::string fileName, std::vector<Matrix>* matricesPointer);
bool isCorrectMatricesInput(std::vector<Matrix> matrices);
