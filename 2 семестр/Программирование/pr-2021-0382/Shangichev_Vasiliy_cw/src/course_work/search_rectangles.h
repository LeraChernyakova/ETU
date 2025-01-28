#ifndef SEARCH_RECTANGLES_H
#define SEARCH_RECTANGLES_H
#include "png_structs.h"


void find_rectangles(struct Png* image, png_byte* rectangle_color, png_byte* line_color, int line_width);
void search_rectangle(struct Png* image, Edge start, Rectangle* rectangle, png_byte* rectangle_color);
int find_down(struct Png* image, Edge start, Edge* diagonal, png_byte* rectangle_color);
int find_right(struct Png* image, Edge start, Edge* diagonal, png_byte* rectangle_color);
Edge find_diagonal(struct Png* image, Edge start, png_byte* rectangle_color);
int next_step_to_diagonal(struct Png* image, Edge start, Edge diagonal, png_byte* rectangle_color);
int next_step_to_right(struct Png* image, Edge start, Edge diagonal, png_byte* rectangle_color);
int next_step_to_down(struct Png* image, Edge start, Edge diagonal, png_byte* rectangle_color);

#endif // SEARCH_RECTANGLES_H
