#include "png_structs.h"

int equal(png_byte* image_pixel, png_byte* color, int width){
    /* compare two pixels */
    for (int i = 0; i < width; i++){
        if (image_pixel[i] != color[i]){
            return 0;
        }
    }
    return 1;
}

void replace(png_byte* image_pixel, png_byte* color, int width){
    /* replaces one pixel with another */
    for (int i = 0; i < width; i++){
        image_pixel[i] = color[i];
    }
}

void change_color(struct Png* image, png_byte* replaced_color, png_byte* color_to_replace){
    int x, y;
    for (y = 0; y < image->height; y++){
        png_byte* row = image->row_pointers[y];
        for (x = 0; x < image->width; x++){
            png_byte* ptr = &(row[x * image->pixel_width]);

            if (equal(ptr, replaced_color, image->pixel_width)){
                replace(ptr, color_to_replace, image->pixel_width);
            }
        }
    }
}

int in(int y, int x, Rectangle rectangle){
    return (rectangle.left_top.y <= y && y <= rectangle.right_bottom.y) && \
    (rectangle.left_top.x <= x && x <= rectangle.right_bottom.x);
}

int checked(int y, int x, Rectangle* rectangles, int len){
    for (int i = 0; i < len; i++){
        if (in(y, x, rectangles[i])){
            return 1;
        }
    }

    return 0;
}
