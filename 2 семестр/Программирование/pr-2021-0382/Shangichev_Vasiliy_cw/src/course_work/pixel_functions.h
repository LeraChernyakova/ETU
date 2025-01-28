#ifndef PIXEL_FUNCTIONS_H
#define PIXEL_FUNCTIONS_H
#include "png_structs.h"

int equal(png_byte* image_pixel, png_byte* color, int width);
void replace(png_byte* image_pixel, png_byte* color, int width);
void change_color(struct Png* image, png_byte* replaced_color, png_byte* color_to_replace);
int in(int y, int x, Rectangle rectangle);
int checked(int y, int x, Rectangle* rectangles, int len);

#endif // PIXEL_FUNCTIONS_H
