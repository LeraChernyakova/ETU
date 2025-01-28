#ifndef GET_ORNAMENT_H
#define GET_ORNAMENT_H
#include "png_structs.h"

void get_ornament(struct Png* image, int ornament_width, png_byte* color, png_byte* second_color);
void get_frame(struct Png* image, png_byte* line_color, int line_width, Rectangle rectangle);

#endif // GET_ORNAMENT_H
