#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <CL/cl.h>
#include <iostream>
#include <vector>

void save_image(const cl_uint* pix, int w, int h, const char* fileName);
int align(int x, int y);
