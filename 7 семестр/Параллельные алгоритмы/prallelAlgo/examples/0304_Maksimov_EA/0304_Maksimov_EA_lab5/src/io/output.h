#pragma once

#include <iostream>
#include <fstream>
#include <CL/cl.h>

#include "files.h"

void writeResult(const cl_uint* pixels, int w, int h);
bool openOutputFile(std::string fileName);
void closeOutputFile();
