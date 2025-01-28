#pragma once

void hexagon_flood_fill(int x, int y, Rgb **arr, Rgb *new_color, Rgb *boarder_color);
void get_hexpoints(int x, int y, int r, Rgb **arr, Point *points_arr);
int transformation(Hexagon *hexagon);
int DrawHexagon(Hexagon *hexagon, Rgb **arr, File *file);
