#pragma once

int check_correct_copy_coordinates(Area *area, File *file);
Rgb **create_cpy_area(Rgb **arr, Area *area);
void free_copy_area(Rgb **arr, Area *area);
int CopyAreaFunc(Rgb **arr, Area *area, File *file);
