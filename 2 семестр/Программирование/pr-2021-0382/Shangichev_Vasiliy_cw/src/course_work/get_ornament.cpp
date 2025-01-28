#include "png_structs.h"
#include "pixel_functions.h"

void get_frame(struct Png* image, png_byte* line_color, int line_width, Rectangle rectangle){
    // define region of frame and rectangle

    Rectangle region;
    region.left_top.x = rectangle.left_top.x - line_width;
    region.left_top.y = rectangle.left_top.y - line_width;

    region.right_bottom.x = rectangle.right_bottom.x + line_width;
    region.right_bottom.y = rectangle.right_bottom.y + line_width;


    int i, j;
    for (i = region.left_top.y; i <= region.right_bottom.y; i++){
        if (i >= image->height || i < 0){
            continue;
        }
        png_byte* row = image->row_pointers[i];
        for (j = region.left_top.x; j <= region.right_bottom.x; j++){
            if (j >= image->width || j < 0){
                continue;
            }
            png_byte* ptr = &(row[j * image->pixel_width]);

            if (!in(i, j, rectangle)){
                replace(ptr, line_color, image->pixel_width);
            }
        }
    }
}

void get_ornament(struct Png* image, int ornament_width, png_byte* color, png_byte* second_color){
    Rectangle old_image;
    int i;

    old_image.left_top.x = ornament_width;
    old_image.left_top.y = ornament_width;

    old_image.right_bottom.x = image->width + ornament_width - 1;
    old_image.right_bottom.y = image->height + ornament_width - 1;

    int new_height = image->height + 2 * ornament_width;
    int new_width = image->width + 2 * ornament_width;
    png_byte** new_image = (png_byte**)malloc(sizeof(png_byte*) * new_height * image->pixel_width);
    for (i = 0; i < new_height; i++){
        new_image[i] = (png_byte*)malloc(sizeof(png_byte) * new_width * image->pixel_width);
    }


    for (i = 0; i < new_height; i++){
        png_byte* new_row = new_image[i];
        for (int j = 0; j < new_width; j++){
            png_byte* new_pixel = &(new_row[j * image->pixel_width]);

            if (in(i, j, old_image)){

                png_byte* old_row = image->row_pointers[i - ornament_width];
                png_byte* old_pixel = &(old_row[(j - ornament_width) * image->pixel_width]);
                replace(new_pixel, old_pixel, image->pixel_width);
            } else {
                replace(new_pixel, color, image->pixel_width);
            }

        }
    }

    for (i = 0; i < image->height; i++){
        free(image->row_pointers[i]);
    }
    free(image->row_pointers);

    image->row_pointers = new_image;
    image->width = new_width;
    image->height = new_height;


    Rectangle first_frame;
    first_frame.left_top.x = ornament_width / 3;
    first_frame.left_top.y = ornament_width / 3;

    first_frame.right_bottom.x = image->width - ornament_width / 3 - 1;
    first_frame.right_bottom.y = image-> height - ornament_width / 3 - 1;

    get_frame(image, second_color, ornament_width / 3, first_frame);
    get_frame(image, second_color, ornament_width / 3, old_image);
}

