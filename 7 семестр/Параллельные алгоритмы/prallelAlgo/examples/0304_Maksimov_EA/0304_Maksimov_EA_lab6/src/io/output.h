#pragma once

#include <iostream>
#include <fstream>

#include "files.h"

bool openOutputFile();
void writeMatrixPlainArrayToFile(int* plainArray, int rows);
void closeOutputFile();
