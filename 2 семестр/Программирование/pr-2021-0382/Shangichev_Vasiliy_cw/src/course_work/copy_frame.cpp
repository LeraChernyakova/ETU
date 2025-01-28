#include "png_structs.h"
#include "pixel_functions.h"

void copy_frame(struct Png* image, FrameCopy coords){
    int i, j;

    int frame_height = coords.right_bottom.y - coords.left_top.y;
    int frame_width = coords.right_bottom.x - coords.left_top.x;


    png_byte** frame = (png_byte**)malloc(sizeof(png_byte*) * frame_height);
    for (i = 0; i < frame_height; i++){
        frame[i] = (png_byte*)malloc(sizeof(png_byte) * frame_height * image->pixel_width);
    }

    for (i = coords.left_top.y; i < coords.left_top.y + frame_height; i++){
        png_byte* row = image->row_pointers[i];
        png_byte* frame_row = frame[i - coords.left_top.y];
        for (j = coords.left_top.x; j < coords.left_top.x + frame_width; j++){
            png_byte* ptr = &(row[j * image->pixel_width]);
            png_byte* frame_ptr = &(frame_row[(j - coords.left_top.x) * image->pixel_width]);
            replace(frame_ptr, ptr, image->pixel_width);
        }
    }

    for (i = coords.destination.y; i - coords.destination.y < frame_height; i++){
        if (i >= image->height || i < 0){
            continue;
        }
        png_byte* row = image->row_pointers[i];
        png_byte* frame_row = frame[i - coords.destination.y];
        for (j = coords.destination.x; j - coords.destination.x < frame_width; j++){
            if (j >= image->width || j < 0){
                continue;
            }
            png_byte* ptr = &(row[j * image->pixel_width]);
            png_byte* frame_ptr = &(frame_row[(j - coords.destination.x) * image->pixel_width]);
            replace(ptr, frame_ptr, image->pixel_width);
        }
    }

    for (i = 0; i < frame_height; i++){
        free(frame[i]);
    }
    free(frame);
}
