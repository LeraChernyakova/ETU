#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>


struct Png {
    unsigned int width, height;
    png_byte color_type; //беззнаковая однобайтовая переменная
    png_byte bit_depth;
    png_structp png_ptr; //объект типа картинка
    png_infop info_ptr;
    //int number_of_passes;
    png_bytep* row_pointers; //массив для доступа к каждому пикселю, указатель на указатель на bytep
};

void print_help() {
    printf("Описание функций, которые выполняет программа. Пожалуйста, передавайте аргументы через запятую!\n");
    printf("-s --square, рисование квадрата. Нужно указать такие параметры, как:\n"
           "1)координаты верхнего левого угла\n"
           "2)размер стороны квадрата\n"
           "3)толщина линий\n"
           "4)цвет линий\n"
           "5)осуществлять заливку или нет\n"
           "6)если выбрана заливка, указать ее цвет\n\n");
    printf("-f --fragment, поменять местами 4 куска области. Нужно указать такие параметры, как:\n"
           "1)координаты верхнего левого угла области\n"
           "2)координаты правого нижнего угла области\n"
           "3)способ обмена частей: по кругу, по диагонали\n\n");
    printf("-c --color, нахождение самого часто встречаемого цвета.\n"
           "Указать, в какой цвет нужно перекрасить его.\n\n");
    printf("-a --a_inversion, инверсия цвета в заданной области. Параметры:\n"
           "1)координаты верхнего левого угла области\n"
           "2)координаты нижнего правого угла области\n");
    printf("-i --information, информация о файле.\n");
    printf("-h --help, инструкция к программе.\n");
}

void print_info(struct Png* image) {
    printf("Ширина изображения в пикселях: %d, "
           "высота изображения в пикселях: %d\n", image->height, image->width);
    printf("Тип цвета: %u\n", image->color_type);
    printf("Глубина цвета: %u\n", image->bit_depth);
}

int read_png_file(char* file_name, struct Png* image) {
    char header[8];
    FILE* file = fopen(file_name, "rb"); //открывает двоичный файл для чтения
    if (!file) {
        printf("Ошибка при чтении файла\n");
        return 0;
    }
    fread(header, 1, 8, file);
    if (png_sig_cmp(header, 0, 8)) {
        printf("Ошибка: формат не PNG\n");
        return 0;
    }

    //Инициализация, создание структур для чтения изображения
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (image->png_ptr == NULL) {
        printf("Ошибка: не удалось создать структуру\n");
        return 0;
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (image->info_ptr == NULL) {
        printf("Ошибка: не удалось создать структуру, в которой хранится"
               "информация об изображении PNG\n");
        return 0;
    }
    if (setjmp(png_jmpbuf(image->png_ptr))) {   //проверка ошибок при использовании библиотеки libpng
        printf("Ошибка инициализации\n");
        return 0;
    }
    png_init_io(image->png_ptr, file); //устанавливает файл для чтения
    png_set_sig_bytes(image->png_ptr, 8); //считываем первые 8 байт
    png_read_info(image->png_ptr, image->info_ptr); //чтение информации

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);

    png_read_update_info(image->png_ptr, image->info_ptr); //выделение памяти дл хранения изображения

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Ошибка чтения изображения");
        return 0;
    }

    image->row_pointers = (png_bytep*)malloc(image->height*sizeof(png_bytep)); //выделение памяти
    for (int y = 0; y < image->height; y++) {
        image->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr)); //выделение памяти для каждой строки пикселей, функция возвращает количество байт, необходимых для хранения строки

    }
    png_read_image(image->png_ptr, image->row_pointers); //считывает данные изобображения в выделенную память

    if (png_get_color_type(image->png_ptr, image->info_ptr) != PNG_COLOR_TYPE_RGBA &&
    png_get_color_type(image->png_ptr, image->info_ptr) != PNG_COLOR_TYPE_RGB) {
        printf("Неподдерживаемый тип палитры\n");
        return 0;
    }
    fclose(file);
    return 1;
}

void write_png_file(char *file_name, struct Png *image) {
    if (file_name[strlen(file_name)-1] != 'g' && file_name[strlen(file_name)-2] != 'n' &&
        file_name[strlen(file_name)-3] != 'p' && file_name[strlen(file_name)-4] != '.') {
        printf("Для записи результата не был передан файл с расширением png.\n");
        return;
    }
    FILE* file = fopen(file_name, "wb"); // создает двоичный файл для записи
    if (!file) {
        printf("Ошибка при создании файла\n");
        return;
    }

    //инициализация структур для записив файл
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (image->png_ptr == NULL) {
        printf("Ошибка: не удалось создать структуру\n");
        return;
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (image->info_ptr == NULL) {
        printf("Ошибка: не удалось создать структуру, в которой хранится"
               "информация об изображении PNG\n");
        return;
    }
    if (setjmp(png_jmpbuf(image->png_ptr))) {   //проверка ошибок при использовании библиотеки libpng
        printf("Ошибка инициализации\n");
        return;
    }

    png_init_io(image->png_ptr, file); //устанавливает файл для записи
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Ошибка при записи заголовка\n");
        return;
    }

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Ошибка при записи данных изображения\n");
        return;
    }
    png_write_image(image->png_ptr, image->row_pointers); //запись карты пикселей

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Ошибка при окончании записи\n");
        return;
    }
    png_write_end(image->png_ptr, NULL);
    for (int y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);
    fclose(file);
}

void draw_square(struct Png* image, int x0, int y0, int a, int t, int r_c,
        int g_c, int b_c, int filling) {
    if (x0 < 0 || y0 < 0 || a < 0 || t < 0)  {
        printf("Недопустимые параметры:\n "
               "координаты, размер квадрата и ширина контура не могут "
               "иметь отрицательные значения\n");
        return;
    }
    if (x0 > image->width || y0 > image->height) {
        printf("Недопустимые параметры:\n "
               "координаты не могут лежать за пределами изображения\n");
        return;
    }
    if ((x0 + a) >= image->width || (y0 + a) >= image->height) {
        printf("Квадрат не может заходить за пределы изображения\n");
        return;
    }
    if (r_c > 255 || r_c < 0 || g_c > 255 || g_c < 0 || b_c > 255 || b_c < 0) {
        printf("Некорректно заданные диапазоны.\n");
        return;
    }
    for (int y = y0; y < y0 + a; y++) {
        png_bytep row1 = image->row_pointers[y];
        for (int x = x0; x < x0 + a; x++) {
            png_bytep ptr1 = &(row1[x * 4]);
            if ((x - x0) < t || (y - y0) < t || ((x0 + a) - x) <= t || ((y0 + a) - y) <= t) {
                ptr1[0] = r_c;
                ptr1[1] = g_c;
                ptr1[2] = b_c;
                ptr1[3] = 255;
            }
        }
    }
    if (filling == 1) {
        int r_f, g_f, b_f;
        scanf("%d,%d,%d", &r_f, &g_f, &b_f);
        if (r_f > 255 || r_f < 0 || g_f > 255 || g_f < 0 || b_f > 255 || b_f < 0 ) {
            printf("Некорректно заданные диапазоны.\n");
            return;
        }
        for (int y = y0 + t; y < y0 + a - t; y++) {
            png_bytep row2 = image->row_pointers[y];
            for (int x = x0 + t; x < x0 + a - t; x++) {
                png_bytep ptr2 = &(row2[x*4]);
                ptr2[0] = r_f;
                ptr2[1] = g_f;
                ptr2[2] = b_f;
                ptr2[3] = 255;
            }
        }
    }
    else if (filling != 0){
        printf("Опция заливки выбрана некорректно.\n");
        return;
    }
}

void fragment_changing(struct Png* image, struct Png* copy, int x1, int y1, int x2, int y2, int option) {
    int x, y;
    if (x1 < 0 ||  y1 < 0 || x2 < 0 || y2 < 0) {
        printf("Ошибка: координаты не могут иметь отрицательные значений\n");
        return;
    }
    if (x1 > image->width || y1 > image->height || x2 > image->width || y2 > image->height) {
        printf("Ошибка: координаты не должны быть за пределами изображения.\n");
        return;
    }
    if (x1 > x2 || y1 > y2) {
        printf("Ошибка: координаты верхнего левого угла должны быть меньше координат"
               "нижнего правого угла.\n");
        return;
    }
    int w_f = (x2 - x1)/2;
    int h_f = (y2 - y1)/2;
    if (option == 1) {
        for (y = y1; y < y1 + h_f; y++) {
            png_bytep row = image->row_pointers[y];
            png_bytep row_change = image->row_pointers[y+h_f];
            for (x = x1; x < x1 + w_f; x++) {
                png_bytep ptr = &(row[x*4]);
                png_bytep ptr_change = &(row_change[x*4]);
                ptr[0] = ptr_change[0];
                ptr[1] = ptr_change[1];
                ptr[2] = ptr_change[2];
                ptr[3] = ptr_change[3];
            }

        }
        for (y = y1 + h_f; y < y2; y++) {
            png_bytep row = image->row_pointers[y];
            png_bytep row_change = image->row_pointers[y];
            for (x = x1; x < x1 + w_f; x++) {
                png_bytep ptr = &(row[x*4]);
                png_bytep ptr_change = &(row_change[(x+w_f)*4]);
                ptr[0] = ptr_change[0];
                ptr[1] = ptr_change[1];
                ptr[2] = ptr_change[2];
                ptr[3] = ptr_change[3];

            }
        }
        for (y = y1 + h_f; y < y2; y++) {
            png_bytep row = image->row_pointers[y];
            png_bytep row_change = image->row_pointers[y-h_f];
            for (x = x1 + w_f; x < x2; x++) {
                png_bytep ptr = &(row[x*4]);
                png_bytep ptr_change = &(row_change[x*4]);
                ptr[0] = ptr_change[0];
                ptr[1] = ptr_change[1];
                ptr[2] = ptr_change[2];
                ptr[3] = ptr_change[3];
            }
        }
        for (y = y1; y < y1 + h_f; y++) {
            png_bytep row = image->row_pointers[y];
            png_bytep row_change = copy->row_pointers[y];
            for (x = x1 + w_f; x < x2; x++) {
                png_bytep ptr = &(row[x*4]);
                png_bytep ptr_change = &(row_change[(x-w_f)*4]);
                ptr[0] = ptr_change[0];
                ptr[1] = ptr_change[1];
                ptr[2] = ptr_change[2];
                ptr[3] = ptr_change[3];
            }
        }
    }
    else if (option == 2) {
        for (y = y1; y < y1 + h_f; y++) {
            png_bytep row1 = image->row_pointers[y];
            png_bytep row2 = image->row_pointers[y+h_f];
            png_bytep row_change1 = copy->row_pointers[y];
            png_bytep row_change2 = image->row_pointers[y+h_f];
            for (x = x1; x < x1 + w_f; x++) {
                png_bytep ptr1 = &(row1[x*4]);
                png_bytep ptr_change1 = &(row_change2[(x+w_f)*4]);
                ptr1[0] = ptr_change1[0];
                ptr1[1] = ptr_change1[1];
                ptr1[2] = ptr_change1[2];
                ptr1[3] = ptr_change1[3];
                png_bytep ptr2 = &(row2[(x+w_f)*4]);
                png_bytep ptr_change2 = &(row_change1[x*4]);
                ptr2[0] = ptr_change2[0];
                ptr2[1] = ptr_change2[1];
                ptr2[2] = ptr_change2[2];
                ptr2[3] = ptr_change2[3];
            }
        }
        for (y = y1; y < y1 + h_f; y++) {
            png_bytep row1 = image->row_pointers[y];
            png_bytep row2 = image->row_pointers[y + h_f];
            png_bytep row_change1 = copy->row_pointers[y];
            png_bytep row_change2 = image->row_pointers[y + h_f];
            for (x = x1 + w_f; x < x2; x++) {
                png_bytep ptr1 = &(row1[x * 4]);
                png_bytep ptr_change1 = &(row_change2[(x - w_f) * 4]);
                ptr1[0] = ptr_change1[0];
                ptr1[1] = ptr_change1[1];
                ptr1[2] = ptr_change1[2];
                ptr1[3] = ptr_change1[3];
                png_bytep ptr2 = &(row2[(x - w_f) * 4]);
                png_bytep ptr_change2 = &(row_change1[x * 4]);
                ptr2[0] = ptr_change2[0];
                ptr2[1] = ptr_change2[1];
                ptr2[2] = ptr_change2[2];
                ptr2[3] = ptr_change2[3];
            }
        }
    }
    else {
        printf("Опция перестановки фрагментов введена некоррректно: "
               "может принимать только значения 1 или 2\n");
        return;
    }
}

void color_changing(struct Png* image, int r_new, int g_new, int b_new) {
    if (r_new > 255 || r_new < 0 || g_new > 255 || g_new < 0 || b_new > 255 || b_new < 0) {
        printf("Данные заданы некорректно, недопустимый диапазон значений.\n");
        return;
    }
    int ***array_colors = calloc(256, sizeof(int**));
    {
        for (int y = 0; y < 256; y++) {
            array_colors[y] = calloc(256, sizeof(int*));
            for (int x = 0; x < 256; x++) {
                array_colors[y][x] = calloc(256, sizeof(int));
            }
        }
    }
    for (int y = 0; y < image->height; y++) {
        png_bytep row = image->row_pointers[y];
        for (int x = 0; x < image->width; x++) {
            png_bytep ptr = &(row[x*4]);
            array_colors[ptr[0]][ptr[1]][ptr[2]]++;
        }
    }
    int max_freq = array_colors[0][0][0];
    int max_r = 0, max_g = 0, max_b = 0;
    for (int y = 0; y < 256; y++) {
        for (int x = 0; x < 256; x++) {
            for (int z = 0; z < 256; z++) {
                if (array_colors[y][x][z] > max_freq) {
                    max_r = y;
                    max_g = x;
                    max_b = z;
                    max_freq = array_colors[y][x][z];
                }
            }
        }
    }
    for (int y = 0; y < image->height; y++) {
        png_bytep row2 = image->row_pointers[y];
        for (int x = 0; x < image->width; x++) {
            png_bytep ptr2 = &(row2[x*4]);
            if (ptr2[0] == max_r && ptr2[1] == max_g && ptr2[2] == max_b) {
                ptr2[0] = r_new;
                ptr2[1] = g_new;
                ptr2[2] = b_new;
            }
        }
    }
    for (int y = 0; y < 256; y++) {
        for (int x = 0; x < 256; x++) {
            free(array_colors[y][x]);
        }
    }
    for (int y = 0; y < 256; y++) {
        free(array_colors[y]);
    }
    free(array_colors);
}


void area_inversion(struct Png* image, int x1, int y1, int x2, int y2) {
    int x, y;
    if (x1 < 0 ||  y1 < 0 || x2 < 0 || y2 < 0) {
        printf("Ошибка: координаты не могут иметь отрицательные значения\n");
        return;
    }
    if (x1 > image->width || y1 > image->height || x2 > image->width || y2 > image->height) {
        printf("Ошибка: координаты не должны быть за пределами изображения.\n");
        return;
    }
    if (x1 > x2 || y1 > y2) {
        printf("Ошибка: координаты верхнего левого угла должны быть меньше координат"
               "нижнего правого угла.\n");
        return;
    }
    for (y = y1; y < y2; y++) {
        png_bytep row = image->row_pointers[y];
        for (x = x1; x < x2; x++) {
            png_bytep ptr = &(row[x*4]);
            ptr[0] = 255 - ptr[0];
            ptr[1] = 255 - ptr[1];
            ptr[2] = 255 - ptr[2];
        }
    }
}

int main(int num_arg, char **argv) {
    static const char* optStr = "s:f:c:a:ih?";
    static const struct option longOpt[] = {
        {"square", required_argument, NULL, 's'},
        {"fragment", required_argument, NULL, 'f'},
        {"color", required_argument, NULL, 'c'},
        {"a_inversion", required_argument, NULL, 'a'},
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {NULL, no_argument, NULL, 0}
    };
    struct Png image;
    int longInd;
    int opt = getopt_long(num_arg, argv, optStr, longOpt, &longInd);
    if (opt == -1) {
        print_help();
        return 0;
    }
    while(opt!=-1) {
        switch (opt) {
            case 's': {
                if (read_png_file(argv[1], &image)) {
                    read_png_file(argv[1], &image);
                    int x0, y0, a, t, r_c, g_c, b_c, filling;
                    int count_arg = sscanf(optarg, "%d,%d,%d,%d,%d,%d,%d,%d", &x0, &y0, &a, &t, &r_c,
                                           &g_c, &b_c, &filling);
                    if (count_arg < 8) {
                        printf("Недостаточно аргументов, вы ввели не все значения!\n");
                        return 0;
                    }
                    draw_square(&image, x0, y0, a, t, r_c, g_c, b_c, filling);
                    write_png_file(argv[num_arg - 1], &image);
                }
                break;
            }
            case 'f': {
                if (read_png_file(argv[1], &image)) {
                    read_png_file(argv[1], &image);
                    struct Png copy;
                    read_png_file(argv[1], &copy);
                    int x1, y1, x2, y2, option;
                    int count_arg = sscanf(optarg, "%d,%d,%d,%d,%d", &x1, &y1, &x2, &y2, &option);
                    if (count_arg < 5) {
                        printf("Недостаточно аргументов, вы ввели не все значения!\n");
                        return 0;
                    }
                    fragment_changing(&image, &copy, x1, y1, x2, y2, option);
                    write_png_file(argv[num_arg - 1], &image);
                }
                break;
            }
            case 'c': {
                if (read_png_file(argv[1], &image)) {
                    read_png_file(argv[1], &image);
                    int r_new, g_new, b_new;
                    int count_arg = sscanf(optarg, "%d,%d,%d", &r_new, &g_new, &b_new);
                    printf("Вы здесь\n");
                    if (count_arg < 3) {
                        printf("Недостаточно аргументов, вы ввели не все значения!\n");
                        return 0;
                    }
                    color_changing(&image, r_new, g_new, b_new);
                    write_png_file(argv[num_arg - 1], &image);
                }
                break;
            }
            case 'a': {
                if (read_png_file(argv[1], &image)) {
                    read_png_file(argv[1], &image);
                    int x1, y1, x2, y2;
                    int count_arg = sscanf(optarg, "%d,%d,%d,%d", &x1, &y1, &x2, &y2);
                    if (count_arg < 4) {
                        printf("Недостаточно аргументов, вы ввели не все значения!\n");
                        return 0;
                    }
                    area_inversion(&image, x1, y1, x2, y2);
                    write_png_file(argv[num_arg - 1], &image);
                }
                break;

            }
            case 'i': {
                print_info(&image);
                break;
            }
            case 'h':
            case '?': {
                print_help();
                return 0;
            }
            default: {
                printf("Опция не существует.\n");
            }
        }
        opt = getopt_long(num_arg, argv, optStr, longOpt, &longInd);
    }
    return 0;
}

