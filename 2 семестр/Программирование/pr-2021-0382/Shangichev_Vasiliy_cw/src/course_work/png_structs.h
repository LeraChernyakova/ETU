#ifndef PNG_STRUCTS_H
#define PNG_STRUCTS_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "png.h"


typedef struct Edge{
    /* this struct determines coordinates
       of edge */
    int x, y;
} Edge;

typedef struct FrameCopy{
    /* struct for coping frame */
    Edge left_top;
    Edge right_bottom;
    Edge destination;
} FrameCopy;

typedef struct Rectangle{
    Edge left_top;
    Edge right_bottom;
} Rectangle;

struct Png{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
    int pixel_width;
};
#endif // PNG_STRUCTS_H
