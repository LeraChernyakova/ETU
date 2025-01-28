#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <string.h>
#include <getopt.h>

struct Png{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    png_byte **row_pointers;
};

void print_info(struct Png *image){
    printf("Ширина в пикселях: %d\n", image->width);
    printf("Высота в пикселях: %d\n", image->height);
    printf("Тип цвета: %u\n", image->color_type);
    printf("Глубина цвета: %u бит\n", image->bit_depth);
}

void printHelp(){
    printf("Это программа с CLI для редактирования png файлов, версия программы 0.0001 :)\n");
    printf("Поддерживаются только файлы с глубиной цвета RGB!\n");
    printf("Формат ввода: ./bmpedit [имя исходного файла] [функция] -[ключ1]/--[полный ключ1] [аргумент1] ...\n\n");
    printf("Функции/ключи:\n");
    printf("triangle [имя файла] - рисование треугольника с возможностью его залить и выбрать цвет.\n");
    printf("    -f/--first  [<x-координата>.<y-координата>] - первая вершина треугольника\n");
    printf("    -s/--second  [<x-координата>.<y-координата>] - вторая вершина треугольника\n");
    printf("    -t/--third [<x-координата>.<y-координата>] - третья вершина треугольника\n");
    printf("    -l/--line [<число>] - толщина сторон треугольника(в пикселях)\n");
    printf("    -C/--color [<число>.<число>.<число>] - цвет заливки и треугольника (RGB)\n");
    printf("    -с/--cast [<число>] - заливка треугольника (по умолчанию без заливки) (1 - заливка, 0 - нет)\n");
    printf("line [имя файла] - рисование прямой линии.\n");
    printf("    -f/--first  [<x-координата>.<y-координата>] - начало линии\n");
    printf("    -s/--second  [<x-координата>.<y-координата>] - конец линии\n");
    printf("    -l/--line [<число>] - толщина линии(в пикселях)\n");
    printf("    -C/--color [<число>.<число>.<число>] - цвет линии (RGB)\n");
    printf("collage [имя файла] - создается коллаж из изображения.\n");
    printf("    -x/--xPhoto  [<число>] - количество изображений по оси X\n");
    printf("    -y/--yPhoto  [<число>] - количество изображений по оси Y\n");
    printf("help - вывод справки о работе программы.\n");
    printf("[имя файла] info - вывод информации об изображении.\n");
    printf("-o/--output [путь] - файл для вывода (по умолчанию исходный файл)\n");
}

void read_png_file(char *file_name, struct Png *image) {
    int y;
    png_byte header[8];

    FILE *fp = fopen(file_name, "rb");

    if (!fp){
        printf("Ошибка открытия файла на чтение!\n");
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)){
        printf("Это не PNG файл!\n");
        exit(-1);
    }

    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        printf("png_create_read_struct failed\n");
        exit(-1);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("png_create_info_struct failed\n");
        exit(-1);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("error during init_io\n");
        exit(-1);
    }

    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);

    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);

    png_read_update_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("error during read_image\n");
        exit(-1);
    }

    image->row_pointers = (png_byte **) malloc(sizeof(png_bytep) * image->height * image->width);
    for (y = 0; y < image->height; y++)
        image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    png_read_image(image->png_ptr, image->row_pointers);

    fclose(fp);
}

int process_file(struct Png *image) {

    if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB){
        return 3;
    }

    printf("Такой тип цвета не поддерживается!\n");
    exit(-1);
}

void write_png_file(char *file_name, struct Png *image) {
    FILE *fp = fopen(file_name, "wb");

    if (!fp){
        printf("Ошибка открытия результирующего файла!\n");
        exit(-1);
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        printf("png_create_write_struct failed\n");
        exit(-1);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("png_create_info_struct failed\n");
        exit(-1);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("error during init_io\n");
        exit(-1);
    }

    png_init_io(image->png_ptr, fp);

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("error during writing header\n");
        exit(-1);
    }

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Ошибка чтения байтов!\n");
        exit(-1);
    }

    png_write_image(image->png_ptr, image->row_pointers);
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("error during end of write\n");
    }

    png_write_end(image->png_ptr, NULL);

    fclose(fp);
}

void draw_Circle(struct Png *image, int x0, int y0, int line_fat, int width_pixel, int Red, int Green, int Blue) {
    int x = 0;
    int radius = line_fat / 2;
    int y = radius;
    int start = y0 - radius;
    int end = y0 + radius;
    int delta = 1 - 2 * radius;
    int error;
    while(y >= 0) {
        png_byte *row = image->row_pointers[y0 + y];
        png_byte *ptr = &(row[(x0 + x) * width_pixel]);
        ptr[0] = Red;
        ptr[1] = Green;
        ptr[2] = Blue;

        png_byte *row1 = image->row_pointers[y0 - y];
        png_byte *ptr1 = &(row1[(x0 + x) * width_pixel]);
        ptr1[0] = Red;
        ptr1[1] = Green;
        ptr1[2] = Blue;

        png_byte *row2 = image->row_pointers[y0 + y];
        png_byte *ptr2 = &(row2[(x0 - x) * width_pixel]);
        ptr2[0] = Red;
        ptr2[1] = Green;
        ptr2[2] = Blue;

        png_byte *row3 = image->row_pointers[y0 - y];
        png_byte *ptr3 = &(row3[(x0 - x) * width_pixel]);
        ptr3[0] = Red;
        ptr3[1] = Green;
        ptr3[2] = Blue;
        error = 2 * (delta + y) - 1;
        while(start <= y0) {
            for (int i = abs(x - x0); i < (x + x0); i++) {
                png_byte *row4 = image->row_pointers[start];
                png_byte *ptr4 = &(row4[i * width_pixel]);
                ptr4[0] = Red;
                ptr4[1] = Green;
                ptr4[2] = Blue;

                png_byte *row5 = image->row_pointers[end];
                png_byte *ptr5 = &(row5[i * width_pixel]);
                ptr5[0] = Red;
                ptr5[1] = Green;
                ptr5[2] = Blue;
            }
            if(error > 0) {
                start++;
                end--;
            }
            break;
        }
        if(delta < 0 && error <= 0) {
            ++x;
            delta += 2 * x + 1;
            continue;
        }
        error = 2 * (delta - x) - 1;
        if(delta > 0 && error > 0) {
            --y;
            delta += 1 - 2 * y;
            continue;
        }
        ++x;
        delta += 2 * (x - y);
        --y;
    }
}

void paint_line(struct Png *image, int width_pixel, int x0, int y0, int x1, int y1, int line_fat, int Red, int Green, int Blue){
    int A, B, sign;
    A = y1 - y0;
    B = x0 - x1;
    if (abs(A) > abs(B)) sign = 1;
    else sign = -1;
    int signa, signb;
    if (A < 0) signa = -1;
    else signa = 1;
    if (B < 0) signb = -1;
    else signb = 1;
    int f = 0;
    png_byte *row = image->row_pointers[y0];
    png_byte *ptr = &(row[x0 * width_pixel]);
    ptr[0] = Red;
    ptr[1] = Green;
    ptr[2] = Blue;
    draw_Circle(image, x0, y0, line_fat, width_pixel, Red, Green, Blue);
    int x = x0, y = y0;
    if (sign == -1){
        do {
            f += A * signa;
            if (f > 0)
            {
                f -= B * signb;
                y += signa;
            }
            x -= signb;
            png_byte *row1 = image->row_pointers[y];
            png_byte *ptr1 = &(row1[x * width_pixel]);
            ptr1[0] = Red;
            ptr1[1] = Green;
            ptr1[2] = Blue;
            draw_Circle(image, x, y, line_fat, width_pixel, Red, Green, Blue);
        } while (x != x1 || y != y1);
    }
    else
    {
        do {
            f += B * signb;
            if (f > 0) {
                f -= A * signa;
                x -= signb;
            }
            y += signa;
            png_byte *row2 = image->row_pointers[y];
            png_byte *ptr2 = &(row2[x * width_pixel]);
            ptr2[0] = Red;
            ptr2[1] = Green;
            ptr2[2] = Blue;
            draw_Circle(image, x, y, line_fat, width_pixel, Red, Green, Blue);
        } while (x != x1 || y != y1);
    }
}

void paint_line_for_triangle(struct Png *image, int width_pixel, int x0, int y0, int x1, int y1,
        int line_fat, png_byte **coordinates, int Red, int Green, int Blue){
    int A, B, sign;
    A = y1 - y0;
    B = x0 - x1;
    if (abs(A) > abs(B)) sign = 1;
    else sign = -1;
    int signa, signb;
    if (A < 0) signa = -1;
    else signa = 1;
    if (B < 0) signb = -1;
    else signb = 1;
    int f = 0;
    png_byte *row = image->row_pointers[y0];
    png_byte *ptr = &(row[x0 * width_pixel]);
    ptr[0] = Red;
    ptr[1] = Green;
    ptr[2] = Blue;
    coordinates[y0][x0] = 1;
    draw_Circle(image, x0, y0, line_fat, width_pixel, Red, Green, Blue);
    int x = x0, y = y0;
    if (sign == -1){
        do {
            f += A * signa;
            if (f > 0)
            {
                f -= B * signb;
                y += signa;
            }
            x -= signb;
            png_byte *row1 = image->row_pointers[y];
            png_byte *ptr1 = &(row1[x * width_pixel]);
            ptr1[0] = Red;
            ptr1[1] = Green;
            ptr1[2] = Blue;
            coordinates[y][x] = 1;
            draw_Circle(image, x, y, line_fat, width_pixel, Red, Green, Blue);
        } while (x != x1 || y != y1);
    }
    else
    {
        do {
            f += B * signb;
            if (f > 0) {
                f -= A * signa;
                x -= signb;
            }
            y += signa;
            png_byte *row2 = image->row_pointers[y];
            png_byte *ptr2 = &(row2[x * width_pixel]);
            ptr2[0] = Red;
            ptr2[1] = Green;
            ptr2[2] = Blue;
            coordinates[y][x] = 1;
            draw_Circle(image, x, y, line_fat, width_pixel, Red, Green, Blue);
        } while (x != x1 || y != y1);
    }
}

void print_triangle(struct Png *image, int width_pixel, int x0, int y0, int x1, int y1, int x2, int y2,
        int line_fat, int flag, int Red, int Green, int Blue){
    int y = 0, x, start_x, end_x;

    png_byte **coordinates = (png_byte **) malloc(sizeof(png_bytep *) * image->height);
    for (int i = 0; i < image->height; i++)
        coordinates[i] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    paint_line_for_triangle(image, width_pixel, x0, y0, x1, y1, line_fat, coordinates, Red, Green, Blue);
    paint_line_for_triangle(image, width_pixel, x1, y1, x2, y2, line_fat, coordinates, Red, Green, Blue);
    paint_line_for_triangle(image, width_pixel, x2, y2, x0, y0, line_fat, coordinates, Red, Green, Blue);
    //заливка треугольника
    if(flag == 1) {
        while(y < image->height){
            int count = 0;
            for(x = 0; x < image->width; x++){
                if(coordinates[y][x] == 1){
                    count += 1;
                    if(count == 1)
                        start_x = x;
                    if(count >= 2) {
                        end_x = x;
                    }
                }
            }
            if(count >= 2){
                for(int k = start_x; k < end_x; k++){
                    png_byte *row = image->row_pointers[y];
                    png_byte *ptr = &(row[k * width_pixel]);
                    ptr[0] = Red;
                    ptr[1] = Green;
                    ptr[2] = Blue;
                }
                y++;
            }else{
                y++;
            }
        }
    }
}

void replace(png_byte* buf, png_byte* for_replace, int width_pixel){
    for (int i = 0; i < width_pixel; i++){
        buf[i] = for_replace[i];
    }
}

void make_collage(struct Png *image, int width_pixel, int x_photos, int y_photos){
    int N, M;
    int y, x, old_x, old_y;

    int new_width = image->width * x_photos;
    int new_height = image->height * y_photos;

    png_byte** new_mas = (png_byte**) malloc(sizeof(png_byte*) * new_height);
    for (y = 0; y < new_height; y++)
        new_mas[y] = (png_byte*) malloc(sizeof(png_byte) * new_width * width_pixel);

    for (y = 0; y < new_height; y++){
        old_y = y % image->height;
        png_byte* old_row = image->row_pointers[old_y];
        png_byte* new_row = new_mas[y];
        for (x = 0; x < new_width; x++){
            old_x = x % image->width;
            png_byte* old_pixel = &(old_row[old_x * width_pixel]);
            png_byte* new_pixel = &(new_row[x * width_pixel]);
            replace(new_pixel, old_pixel, width_pixel);
        }
    }

    for (x = 0; x < image->height; x++){
        free(image->row_pointers[x]);
    }
    free(image->row_pointers);

    image->row_pointers = new_mas;
    image->width = new_width;
    image->height = new_height;
}

void choice(char* func, int key, int* x0, int* y0, int* x1, int* y1, int* x2, int* y2, int* line_fat,
            int* cast, char** output, int* Red, int* Green, int* Blue, int* x_photos, int* y_photos){
    int i = 0;
    switch (key) {
        case 'f':
            *x0 = atoi(optarg);
            while(optarg[i] != '.'){
                i++;
            }
            *y0 = atoi(&optarg[i+1]);
            break;
        case 's':
            *x1 = atoi(optarg);
            while(optarg[i] != '.'){
                i++;
            }
            *y1 = atoi(&optarg[i+1]);
            break;
        case 't':
            *x2 = atoi(optarg);
            while(optarg[i] != '.'){
                i++;
            }
            *y2 = atoi(&optarg[i+1]);
            break;
        case 'l':
            *line_fat = atoi(optarg);
            break;
        case 'c':
            *cast = atoi(optarg);
            break;
        case 'C':
            *Red = atoi(optarg);
            while(optarg[i] != '.'){
                i++;
            }
            *Green = atoi(&optarg[i+1]);
            while(optarg[i] != '.'){
                i++;
            }
            *Blue = atoi(&optarg[i+1]);
            break;
        case 'x':
            *x_photos = atoi(optarg);
            break;
        case 'y':
            *y_photos = atoi(optarg);
            break;
        case 'o':
            *output = optarg;
            break;
        default:
            printf("Нет такого ключа для %s!\n", func);
            exit(-1);
    }
}

int main(int argc, char **argv) {
    struct Png image;
    int index = 0, key;
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0, line_fat = 0, flag = 0;
    int Red = 0, Green = 0, Blue = 0;
    int x_photos = 1, y_photos = 1;
    char* output = argv[1];

    read_png_file(argv[1], &image);
    int width_pixel = process_file(&image);

    const struct option firstCordStruct = {"first", required_argument, NULL, 'f'};
    const struct option secondCordStruct = {"second", required_argument, NULL, 's'};
    const struct option thirdCordStruct = {"third", required_argument, NULL, 't'};
    const struct option fatLineStruct = {"line", required_argument, NULL, 'l'};
    const struct option castStruct = {"cast", required_argument, NULL, 'c'};
    const struct option xPhotosStruct = {"xPhoto", required_argument, NULL, 'x'};
    const struct option yPhotosStruct = {"yPhoto", required_argument, NULL, 'y'};
    const struct option colorStruct = {"color", required_argument, NULL, 'C'};
    const struct option outputStruct = {"output", required_argument, NULL, 'o'};

    opterr = 0;
    if(argc == 1 || !strcmp(argv[2], "help")){
        printHelp();
        return 0;
    }else if(!strcmp(argv[2], "info")){
        print_info(&image);
        return 0;
    }else if(!strcmp(argv[2], "triangle")) {
        struct option options[] = {firstCordStruct, secondCordStruct, thirdCordStruct, fatLineStruct,
                castStruct, colorStruct, outputStruct};
        while((key = getopt_long(argc, argv, "f:s:t:l:c:C:o:", options, &index)) != -1) {
            choice("triangle", key, &x0, &y0, &x1, &y1, &x2, &y2, &line_fat,
                   &flag, &output, &Red, &Green, &Blue, 0, 0);
        }
        print_triangle(&image, width_pixel, x0, y0, x1, y1, x2, y2, line_fat, flag, Red, Green, Blue);
        write_png_file(output, &image);
    }else if(!strcmp(argv[2], "line")) {
        struct option options[] = {firstCordStruct, secondCordStruct, fatLineStruct, colorStruct,
                                    outputStruct};
        while((key = getopt_long(argc, argv, "f:s:l:C:o:", options, &index)) != -1) {
            choice("line", key, &x0, &y0, &x1, &y1, 0, 0,  &line_fat,
                   0, &output, &Red, &Green, &Blue, 0, 0);
        }
        paint_line(&image, width_pixel, x0, y0, x1, y1, line_fat, Red, Green, Blue);
        write_png_file(output, &image);
    }else if(!strcmp(argv[2], "collage")) {
        struct option options[] = {xPhotosStruct, yPhotosStruct, outputStruct};
        while((key = getopt_long(argc, argv, "x:y:o:", options, &index)) != -1) {
            choice("collage", key, 0, 0, 0, 0, 0, 0,  0,
                   0, &output, 0, 0, 0, &x_photos, &y_photos);
        }
        make_collage(&image, width_pixel, x_photos, y_photos);
        write_png_file(output, &image);
    }

    for (int y = 0; y < image.height; y++)
        free(image.row_pointers[y]);
    free(image.row_pointers);

    return 0;
}
