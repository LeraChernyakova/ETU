#pragma once

#include "Cell.h"

bool check_pos(int point, int length);
void placer(Cell& cell, bool with_force);
int new_count(int cur_count, int free_cells);