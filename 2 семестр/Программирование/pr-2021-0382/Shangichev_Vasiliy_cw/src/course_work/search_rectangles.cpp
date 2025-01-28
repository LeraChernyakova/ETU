#include "png_structs.h"
#include "pixel_functions.h"
#include "get_ornament.h"

int next_step_to_down(struct Png* image, Edge start, Edge diagonal, png_byte* rectangle_color){
    // check row
    if (diagonal.y + 1 >= image->height){
        return 0;
    }
    png_byte* row = image->row_pointers[diagonal.y + 1];
    for (int i = start.x; i <= diagonal.x; i++){
        if (!equal(rectangle_color, &(row[i * image->pixel_width]), image->pixel_width)){
            return 0;
        }
    }
    return 1;
}

int next_step_to_right(struct Png* image, Edge start, Edge diagonal, png_byte* rectangle_color){
    // check column
    if (diagonal.x + 1 >= image->width){
        return 0;
    }
    for (int i = start.y; i <= diagonal.y; i++){
        png_byte* row = image->row_pointers[i];
        if (!equal(rectangle_color, &(row[(diagonal.x + 1) * image->pixel_width]), image->pixel_width)){
            return 0;
        }
    }
    return 1;
}

int next_step_to_diagonal(struct Png* image, Edge start, Edge diagonal, png_byte* rectangle_color){

    png_byte* row = image->row_pointers[diagonal.y + 1];
    if (!equal(rectangle_color, &(row[(diagonal.x + 1) * image->pixel_width]), image->pixel_width)){
        return 0;
    }

    if (!next_step_to_right(image, start, diagonal, rectangle_color)){
        return 0;
    }

    if (!next_step_to_down(image, start, diagonal, rectangle_color)){
        return 0;
    }

    return 1;
}

Edge find_diagonal(struct Png* image, Edge start, png_byte* rectangle_color){
    Edge diagonal;
    diagonal.x = start.x;
    diagonal.y = start.y;
    while (next_step_to_diagonal(image, start, diagonal, rectangle_color)){
        diagonal.x++;
        diagonal.y++;
        if ((diagonal.x + 1) >= image->width || (diagonal.y + 1) >= image->height){
            break;
        }
    }
    return diagonal;
}

int find_right(struct Png* image, Edge start, Edge* diagonal, png_byte* rectangle_color){
    int i = 0;
    while (next_step_to_right(image, start, *diagonal, rectangle_color)){
        i = 1;
        diagonal->x += 1;
    }
    return i;
}

int find_down(struct Png* image, Edge start, Edge* diagonal, png_byte* rectangle_color){
    int i = 0;
    while (next_step_to_down(image, start, *diagonal, rectangle_color)){
        i = 1;
        diagonal->y += 1;
    }
    return i;
}

void search_rectangle(struct Png* image, Edge start, Rectangle* rectangle, png_byte* rectangle_color){
    // check coordinates of diagonal
    Edge diagonal = find_diagonal(image, start, rectangle_color);


    if (!find_right(image, start, &diagonal, rectangle_color)){
        find_down(image, start, &diagonal, rectangle_color);
    }

    rectangle->left_top.x = start.x;
    rectangle->left_top.y = start.y;

    rectangle->right_bottom.x = diagonal.x;
    rectangle->right_bottom.y = diagonal.y;
}

void find_rectangles(struct Png* image, png_byte* rectangle_color, png_byte* line_color, int line_width){
    Edge start;
    int num_rectangles = 10;
    int current_rectangle = 0;
    int i, j;
    Rectangle* rectangles = (Rectangle*)malloc(sizeof(Rectangle) * num_rectangles);
    for (i = 0; i < image->height; i++){
        png_byte* row = image->row_pointers[i];
        for (j = 0; j < image->width; j++){
            png_byte *ptr = &(row[j * image->pixel_width]);

            if (equal(ptr, rectangle_color, image->pixel_width)){
                if (!checked(i, j, rectangles, current_rectangle)){
                    // creating new rectangle
                    // check size of array
                    if (current_rectangle == num_rectangles){
                        num_rectangles *= 2;
                        rectangles = (Rectangle*)realloc(rectangles, sizeof(Rectangle) * num_rectangles);
                    }
                    start.y = i;
                    start.x = j;
                    search_rectangle(image, start, &rectangles[current_rectangle++], rectangle_color);

                }
            }
        }
    }


    // set frames of rectangles
    for (i = 0; i < current_rectangle; i++){
        get_frame(image, line_color, line_width, rectangles[i]);
    }

    free(rectangles);

}

