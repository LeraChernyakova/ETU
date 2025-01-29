#ifndef UTILITY
#define UTILITY

#include <iostream>
#include <vector>
#include <fstream>


std::string read_file(const std::string& file_name);
void ppm_draw(std::string const & filename, std::vector<int> const & grid, 
                int width, int height, int iterations);

#endif