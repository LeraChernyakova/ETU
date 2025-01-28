#pragma once

void set_pixel(Rgb *pixel, Rgb *new);
int is_check_color(Rgb *current, Rgb *new);
void draw_rectangle(int x0, int y0, int x1, int y1, Rgb **arr, Rgb *color);
void draw_line(int x0, int y0, int x1, int y1, Rgb **arr, Rgb *color);

