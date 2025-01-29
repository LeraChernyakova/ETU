#pragma once

#include <iostream>
#include <fstream>

#include "../model/matrix.h"
#include "files.h"

void writeMatrixToFile(Matrix matrix);
bool openOutputFile();
void closeOutputFile();
