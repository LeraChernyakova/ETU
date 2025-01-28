#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#define PNG_DEBUG 3
#include <png.h>
#include "class_images.h"

void images::read_png_file(char *file_name) {
    int x,y;

    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    if (!fp){
        std::cout << "File could not be opened\n";
        exit(0);
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp((png_const_bytep)header, 0, 8)){// проверяет сигнатуру PNG
        std::cout << "File is not recognized as a PNG\n";
        exit(0);
    }

    /* initialize stuff */
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);//выделяет память и инициализирует структуру для чтения PNG

    if (!image->png_ptr){
        std::cout << "png_create_read_struct failed\n";
        exit(0);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr); //выделяет память и инициализирует структуру инфо PNG
    if (!image->info_ptr){
        std::cout << "png_create_info_struct failed\n";
        exit(0);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){ // хз, какая-то проверка
        std::cout << "Error during init_io\n";
        exit(0);
    }

    png_init_io(image->png_ptr, fp); //инициализирует ввод для PNG файла
    png_set_sig_bytes(image->png_ptr, 8);// считывает 8 байт сигнатуры

    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);

    if (png_get_color_type(image->png_ptr, image->info_ptr) != PNG_COLOR_TYPE_RGBA){
        std::cout << "Wrong color type, color type of input file must be RGBA";
        exit(0);
    }

    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);

    /* read file */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        std::cout << "Error during read_image\n";
        exit(0);
    }

    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    for (y = 0; y < image->height; y++)
        image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    png_read_image(image->png_ptr, image->row_pointers);

    fclose(fp);
}
void images::write_png_file(char *file_name) {
    int x,y;
    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp){
        std::cout << "Output file could not be opened\n";
        exit(0);
    }

    /* initialize stuff */
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        std::cout << "png_create_write_struct failed\n";
        exit(0);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        std::cout << "png_create_write_struct failed\n";
        exit(0);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        std::cout << "error during init_io\n";
        exit(0);
    }

    png_init_io(image->png_ptr, fp);


    /* write header */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        std::cout << "error during writing header\n";
        exit(0);
    }

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);


    /* write bytes */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        std::cout << "error during writing bytes\n";
        exit(0);
    }

    png_write_image(image->png_ptr, image->row_pointers);


    /* end write */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        std::cout << "error during end of write\n";
        exit(0);
    }

    png_write_end(image->png_ptr, NULL);

    /* cleanup heap allocation */
    for (y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);
    fclose(fp);
}