#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <getopt.h>
#include <ctype.h>

#pragma pack (push, 1)
typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} Rgb;

typedef struct {
    uint16_t signature;
    uint32_t filesize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixelArrOffset;
} BitmapFileHeader;

typedef struct {
    uint32_t headerSize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    uint32_t xPixelsPerMeter;
    uint32_t yPixelsPerMeter;
    uint32_t colorsInColorTable;
    uint32_t importantColorCount;
} BitmapInfoHeader;

#pragma pack(pop)

typedef struct {
    BitmapFileHeader bfh;
    BitmapInfoHeader bih;
    Rgb **pixel_array;
} BmpFile;

int readBmp(char *file_name, BmpFile *bmpf);

void writeBmp(char *file_name, BmpFile *bmpf);

int rgbCmp(Rgb *c1, Rgb *c2);

void changeColor(Rgb ref_color, Rgb color_to_change, BmpFile *bf);

void copyArea(int x0, int y0, int x1, int y1, int x_dest, int y_dest, BmpFile *bf);

void drawLine(int x0, int y0, int x1, int y1, Rgb color, BmpFile *bf);

void drawHexagon(int x_c, int y_c, int r, Rgb color, int thickness, int fill, Rgb fill_color, BmpFile *bf);

void gradientFrame(Rgb start_color, Rgb end_color, int frame_width, BmpFile *bf);

void stripedFrame(Rgb color1, Rgb color2, int frame_width, BmpFile *bf);

void wavyFrame(Rgb color, int thickness, BmpFile *bf);

void getAllKeys(int argc, char *argv[], int p1[][2], int p2[][2], int p3[][2], int *rad, int *thickness, int *fill_flag, int *pattern, Rgb *color1, Rgb *color2, char **wfile);

void printHelp() {
    printf("\nBed - это утилита для редактирование графических файлов в формате \".bmp\".\n");
    printf("Формат поддерживаемых файлов:\n");
    printf("\t* BMP version 3;\n");
    printf("\t* без таблицы цветов;\n");
    printf("\t* глубина цвета - 24 бита;\n");
    printf("\t* без сжатия.\n");
    printf("Формат вызова программы: ./bed [путь к исходному файлу] [название опции] [ключи и аргументы]\n");
    printf("Функции программы:\n");
    printf("\t- Рисование правильного шестиугольника:\n");
    printf("\t\t1) По координатам квадрата - s_hexagon.\n\t\t2) По координиатам центра и радиусу - с_hexagon.\n");
    printf("\t- Копирование выбранной области - copy_area.\n");
    printf("\t- Замена цвета - change_color.\n");
    printf("\t- Рамка в виде узора - pattern_frame.\n");
    printf("\t- Вывод информации о файле - info.\n");
    printf("Ключи:\n \t-s/--start [координата 1].[координата 2] - верхний левый угол квадрата/копируемой области;\n");
    printf("\t-e/--end [координата 1].[координата 2] - нижний правый угол квадрата/копируемой области;\n");
    printf("\t-z/--centre [координата 1].[координата 2] - центр окружности, в которую вписан шестиугольник;\n");
    printf("\t-r/--radius [значение] - радиус этой окружности;\n");
    printf("\t-t/--thickness [значение] - толщина контура шестиугольника/ширина рамки;\n");
    printf("\t-f/--fill - заливка шестиугольника;\n");
    printf("\t-p/--pattern [значение] - выбор узора рамки (1 - градиент, 2 - узор \"в полосочку\", 3 - волнистый узор (1 и 2 задаются двумя цветами));\n");
    printf("\t-c/--color1 [значение красной компоненты].[значение зелёной компоненты].[значение синей компоненты] - цвет границы шестиугольника/заменяемый цвет/начальный цвет градиента/цвет волнистой рамки (по умолчанию чёрный);\n");
    printf("\t-С/--color2 [значение красной компоненты].[значение зелёной компоненты].[значение синей компоненты] - цвет заливки шестиугольника/заменяющий цвет/конечный цвет градиента (по умолчанию чёрный);\n");
    printf("\t-o/--output [название файла] - название файла, в который требуется записать изменённый файл (по умолчанию - это название исходного файла)\n");
}

void printFileHeader(BitmapFileHeader header){
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header){
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width:     \t%x (%u)\n", header.width, header.width);
    printf("height:    \t%x (%u)\n", header.height, header.height);
    printf("planes:    \t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc == 1 || !strcmp(argv[1], "help")) {
        printHelp();
        return 0;
    }

    BmpFile bmpf;
    if (!readBmp(argv[1], &bmpf)) return 0;

    if (argc < 3) {printf("Не введено название опции.\n"); return 0;}
    char *choice = argv[2];

    int p1[2] = {-1, -1}, p2[2] = {-1, -1}, p3[2] = {-1, -1};
    int rad = -1, thick = -1, fill_flag = 0, pattern = -1;
    Rgb color1 = {0, 0, 0}, color2 = {0, 0, 0};
    char *wfile_name = argv[1];

    opterr = 0;
    getAllKeys(argc, argv, &p1, &p2, &p3, &rad, &thick, &fill_flag, &pattern, &color1, &color2, &wfile_name);

    if (!strcmp(choice, "c_hexagon")){
        if (p3[0] == -1 || p3[1] == -1 || p3[0] >= bmpf.bih.width || p3[1] >= bmpf.bih.height)
        {printf("Центр шестиугльника не может находиться вне картинки.\n"); return 0;}
        if (rad == -1) {printf("Неправильно введеён радиус.\n"); return 0;}
        if (thick < 0 || thick > rad/2) {printf("Неправильно введена толщина линии.\n"); return 0;}
        drawHexagon(p3[0], p3[1], rad, color1, thick, fill_flag, color2, &bmpf);
    }

    else if (!strcmp(choice, "s_hexagon")){
        if (p1[0] > p2[0]) {int tmp = p1[0]; p1[0] = p2[0]; p2[0] = tmp;}
        if (p1[1] > p2[1]) {int tmp = p1[1]; p1[1] = p2[1]; p2[1] = tmp;}

        if (p1[1] - p1[0] != p2[1] - p2[0]) { printf("Координаты не образуют квадрат.\n"); return 0;}

        p3[0] = p1[0] + (p2[0] - p1[0]) / 2;
        p3[1] = p1[1] + (p2[1] - p1[1]) / 2;
        rad = (p2[0] - p1[0]) / 2;

        if (p3[0] == -1 || p3[1] == -1 || p3[0] >= bmpf.bih.width || p3[1] >= bmpf.bih.height)
        {printf("Неправильно введены координаты центра.\n"); return 0;}
        if (rad == -1) {printf("Неправильно введеён радиус.\n"); return 0;}
        if (thick < 0 || thick > rad/2) {printf("Неправильно введена толщина линии.\n"); return 0;}
        drawHexagon(p3[0], p3[1], rad, color1, thick, fill_flag, color2, &bmpf);
    }

    else if (!strcmp(choice, "copy_area")){
        if (!(p1[0] >= 0 && p1[0] < bmpf.bih.width &&
              p1[1] >= 0 && p1[1] < bmpf.bih.height &&
              p2[0] >= 0 && p2[0] < bmpf.bih.width &&
              p2[1] >= 0 && p2[1] < bmpf.bih.height &&
              p3[0] >= 0 && p3[0] < bmpf.bih.width &&
              p3[1] >= 0 && p3[1] < bmpf.bih.height))
        {printf("Неверно заданы координаты точек.\n"); return 0;}
        copyArea(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], &bmpf);
    }

    else if (!strcmp(choice, "change_color")){
        changeColor(color2, color1, &bmpf);
    }
    else if (!strcmp(choice, "pattern_frame")){
        if (thick > bmpf.bih.height/3 || thick > bmpf.bih.width/3) {printf("Недопустимая ширина рамки.\n"); return 0;}
        switch (pattern){
            case 1:
                gradientFrame(color1, color2, thick, &bmpf);
                break;
            case 2:
                stripedFrame(color1, color2, thick, &bmpf);
                break;
            case 3:
                wavyFrame(color1, thick, &bmpf);
                break;
            default:
                printf("Неверно задан номер узора.\n");
        }
    }
    else if (!strcmp(choice, "info")){
        printFileHeader(bmpf.bfh);
        printInfoHeader(bmpf.bih);
    }

    else printf("Неизвестное название опции.\n");

    writeBmp(wfile_name, &bmpf);
    return 0;
}

void getAllKeys(int argc, char *argv[], int p1[][2], int p2[][2], int p3[][2], int *rad, int *thickness, int *fill_flag, int *pattern, Rgb *color1, Rgb *color2, char **wfile){
    struct option long_opts[] = {
            {"start", required_argument, NULL, 's'},
            {"end", required_argument, NULL, 'e'},
            {"centre", required_argument, NULL, 'z'},
            {"radius", required_argument, NULL, 'r'},
            {"thickness", required_argument, NULL, 't'},
            {"fill", no_argument, NULL, 'f'},
            {"pattern", required_argument, NULL, 'p'},
            {"color1", required_argument, NULL, 'c'},
            {"color2", required_argument, NULL, 'C'},
            {"output", required_argument, NULL, 'o'},
            {NULL, 0, NULL, 0}
    };
    char *short_opts = "s:r:z:e:r:t:fp:c:C:o:";
    int opt;

    while ((opt = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1){
        switch (opt){
            case 's':{
                int ind = optind - 1;
                int arg_len = strlen(argv[ind]);

                if (!isdigit(argv[ind][0])) break;
                (*p1)[0] = atoi(argv[ind]);

                int i = 0;
                for (; argv[ind][i] != '.'; i++)
                    if (i >= arg_len) break;
                if (i == arg_len) break;

                if (!isdigit(argv[ind][i + 1])) break;
                (*p1)[1] = atoi(&argv[ind][i + 1]);

                break;
            }
            case 'e':{
                int ind = optind - 1;
                int arg_len = strlen(argv[ind]);

                if (!isdigit(argv[ind][0])) break;
                (*p2)[0] = atoi(argv[ind]);

                int i = 0;
                for (; argv[ind][i] != '.'; i++)
                    if (i >= arg_len) break;
                if (i == arg_len) break;

                if (!isdigit(argv[ind][i + 1])) break;
                (*p2)[1] = atoi(&argv[ind][i + 1]);

                break;
            }
            case 'z':{
                int ind = optind - 1;
                int arg_len = strlen(argv[ind]);

                if (!isdigit(argv[ind][0])) break;
                (*p3)[0] = atoi(argv[ind]);

                int i = 0;
                for (; argv[ind][i] != '.'; i++)
                    if (i >= arg_len) break;
                if (i == arg_len) break;

                if (!isdigit(argv[ind][i + 1])) break;
                (*p3)[1] = atoi(&argv[ind][i + 1]);

                break;
            }
            case 'r':{
                if (!isdigit(argv[optind - 1][0])) break;
                *rad = atoi(argv[optind - 1]);
                break;
            }
            case 't':{
                if (!isdigit(argv[optind - 1][0])) break;
                *thickness = atoi(argv[optind - 1]);
                break;
            }
            case 'f':{
                *fill_flag = 1;
                break;
            }
            case 'p':{
                if (!isdigit(argv[optind - 1][0])) break;
                *pattern = atoi(argv[optind - 1]);
                if (*pattern < 1 || *pattern > 3) *pattern = -1;
                break;
            }
            case 'c':{
                int ind = optind - 1;
                int arg_len = strlen(argv[ind]);

                if (!isdigit(argv[ind][0])) break;
                int r = atoi(argv[ind]);
                if (r >= 0 && r <= 255) color1->r = r;

                int i = 0;
                for (; argv[ind][i] != '.'; i++)
                    if (i >= arg_len) break;
                if (i == arg_len) break;
                i ++;

                if (!isdigit(argv[ind][i])) break;
                int g = atoi(&argv[ind][i]);
                if (g >= 0 && g <= 255) color1->g = g;

                for (; argv[ind][i] != '.'; i++)
                    if (i >= arg_len) break;
                if (i == arg_len) break;
                i ++;

                if (!isdigit(argv[ind][i])) break;
                int b = atoi(&argv[ind][i]);
                if (b >= 0 && b <= 255) color1->b = b;

                break;
            }
            case 'C':{
                int ind = optind - 1;
                int arg_len = strlen(argv[ind]);

                if (!isdigit(argv[ind][0])) break;
                int r = atoi(argv[ind]);
                if (r >= 0 && r <= 255) color2->r = r;

                int i = 0;
                for (; argv[ind][i] != '.'; i++)
                    if (i >= arg_len) break;
                if (i == arg_len) break;
                i ++;

                if (!isdigit(argv[ind][i])) break;
                int g = atoi(&argv[ind][i]);
                if (g >= 0 && g <= 255) color2->g = g;

                for (; argv[ind][i] != '.'; i++)
                    if (i >= arg_len) break;
                if (i == arg_len) break;
                i ++;

                if (!isdigit(argv[ind][i])) break;
                int b = atoi(&argv[ind][i]);
                if (b >= 0 && b <= 255) color2->b = b;

                break;
            }
            case 'o':{
                *wfile = argv[optind - 1];
            }
            default:
                break;
        }
    }
}


int readBmp(char*file_name, BmpFile *bmpf) {

    FILE *f = fopen(file_name, "rb");
    if (!f) {
        printf("Ошибка при открытии файла.\n");
        return 0;
    }


    BitmapFileHeader *bfh = &bmpf->bfh;
    BitmapInfoHeader *bih = &bmpf->bih;

    fread(bfh, sizeof(BitmapFileHeader), 1, f);
    if (bfh->signature != 0x4d42) {
        printf("Неверный формат файла.\n");
        return 0;
    }

    fread(bih, sizeof(BitmapInfoHeader), 1, f);
    if (bih->compression != 0 || bih->colorsInColorTable != 0 || bih->bitsPerPixel != 24) {
        printf("Непооддерживаемая версия формата.\n");
        return 0;
    }

    fseek(f, bfh->pixelArrOffset, SEEK_SET);
    unsigned int image_height = bih->height;
    unsigned int image_width = bih->width;

    Rgb **image = calloc(image_height, sizeof(Rgb *));
    unsigned long padded_width = image_width * sizeof(Rgb) + image_width * sizeof(Rgb) % 4;
    for (int i = 0; i < image_height; i++) {
        image[i] = calloc(padded_width, 1);
        fread(image[i], 1, padded_width, f);
    }

    bmpf->pixel_array = image;

    fclose(f);
    return 1;
}

void drawLine(int x0, int y0, int x1, int y1, Rgb color, BmpFile *bf) {
    unsigned int image_height = bf->bih.height;
    unsigned int image_width = bf->bih.width;

    int dx = abs(x1 - x0), dy = abs(y1 - y0);
    int cur_x = x0, cur_y = y0;

    if (dx >= dy) {
        int err = 0;
        int derr = dy + 1;
        int x_dir = (x1 == x0) ? 0 : (x1 > x0 ? 1 : -1), y_dir = (y1 == y0) ? 0 : (y1 > y0 ? 1 : -1);

        for (int i = 0; i <= dx; i++) {
            cur_x += (i == 0 ? 0 : x_dir);
            if (cur_y < image_height && cur_y >= 0 && cur_x < image_width && cur_x >= 0)
                bf->pixel_array[cur_y][cur_x] = color;
            err = err + derr;
            if (err >= dx + 1) {
                cur_y += y_dir;
                err = err - (dx + 1);
            }
        }
    } else {
        int err = 0;
        int derr = dx + 1;
        int x_dir = (x1 == x0) ? 0 : (x1 > x0 ? 1 : -1), y_dir = (y1 == y0) ? 0 : (y1 > y0 ? 1 : -1);

        for (int i = 0; i <= dy; i++) {
            cur_y += (i == 0 ? 0 : y_dir);
            if (cur_y < image_height && cur_y >= 0 && cur_x < image_width && cur_x >= 0)
                bf->pixel_array[cur_y][cur_x] = color;
            err = err + derr;
            if (err >= dy + 1) {
                cur_x += x_dir;
                err = err - (dy + 1);
            }
        }
    }
}

void drawHexagon(int x_c, int y_c, int r, Rgb color, int thickness, int fill, Rgb fill_color, BmpFile *bf) {
    int x[6], y[6];
    for (int i = 0; i < 6; i++) {
        double angle = M_PI / 180 * (60 * i - 30);
        x[i] = x_c + r * cos(angle);
        y[i] = y_c + r * sin(angle);
    }

    for (int j = 0; j < thickness; j++) {
        drawLine(x[0] - j, y[0], x[1] - j, y[1], color, bf);
        for (int i = 1; i < 3; i++) {
            drawLine(x[i], y[i] - j, x[i + 1], y[i + 1] - j, color, bf);
        }
        drawLine(x[3] + j, y[3], x[3] + j, y[4], color, bf);
        for (int i = 4; i < 6; i++) {
            drawLine(x[i], y[i] + j, x[(i + 1) % 6], y[(i + 1) % 6] + j, color, bf);
        }
    }

    if (fill) {
        drawLine(x[0] - thickness, y[0], x[1] - thickness, y[1], color, bf);
        for (int i = 1; i < 3; i++) {
            drawLine(x[i], y[i] - thickness, x[i + 1], y[i + 1] - thickness, color, bf);
        }
        drawLine(x[3] + thickness, y[3], x[3] + thickness, y[4], color, bf);
        for (int i = 4; i < 6; i++) {
            drawLine(x[i], y[i] + thickness, x[(i + 1) % 6], y[(i + 1) % 6] + thickness, color, bf);
        }
        drawHexagon(x_c, y_c, r - thickness, fill_color, r - thickness, 0, color, bf);
    }
}

void copyArea(int x0, int y0, int x1, int y1, int x_dest, int y_dest, BmpFile *bf) {
    Rgb **image = bf->pixel_array;
    unsigned int image_height = bf->bih.height;
    unsigned int image_width = bf->bih.width;

    if (x0 > x1) {
        int tmp = x0;
        x0 = x1;
        x1 = tmp;
    }

    if (y0 > y1) {
        int tmp = y0;
        y0 = y1;
        y1 = tmp;
    }

    int copy_height = y1 - y0;
    int copy_width = x1 - x0;

    //copy of chosen area
    Rgb **area_copy = calloc(copy_height, sizeof(Rgb *));
    for (int i = 0; i < copy_height; i++) {
        area_copy[i] = calloc(copy_width, sizeof(Rgb));
        memcpy(area_copy[i], &image[y0 + i][x0], copy_width * sizeof(Rgb));
    }

    //writing to destination
    for (int i = 0; i < copy_height; i++) {
        if (y_dest - i >= 0) {
            if (x_dest + copy_width < image_width)
                memcpy(&image[y_dest - i][x_dest], area_copy[copy_height - 1 - i], copy_width * sizeof(Rgb));
            else
                memcpy(&image[y_dest - i][x_dest], area_copy[copy_height - 1 - i],
                       (image_width - x_dest) * sizeof(Rgb));
        }
    }
    for (int i = 0; i < copy_height; i++)
        free(area_copy[i]);
    free(area_copy);
}

void changeColor(Rgb ref_color, Rgb color_to_change, BmpFile *bf) {
    unsigned int image_height = bf->bih.height;
    unsigned int image_width = bf->bih.width;
    unsigned long padded_width = image_width * sizeof(Rgb) + image_width * sizeof(Rgb) % 4;


    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < padded_width; j++) {
            if (rgbCmp(&color_to_change, &bf->pixel_array[i][j]))
                bf->pixel_array[i][j] = ref_color;
        }
    }
}

int rgbCmp(Rgb *c1, Rgb *c2) {
    if (abs(c1->r - c2->r) < 10 && abs(c1->b - c2->b) < 10 && abs(c1->g - c2->g) < 10)
        return 1;
    else return 0;
}

void writeBmp(char *file_name, BmpFile *bmpf) {
    unsigned int image_height = bmpf->bih.height;
    unsigned int image_width = bmpf->bih.width;
    unsigned long padded_width = image_width * sizeof(Rgb) + image_width * sizeof(Rgb) % 4;

    FILE *wf = fopen(file_name, "wb");
    if (!wf) {printf("Ошибка при открытия файла на запись.\n"); return;}
    fwrite(&bmpf->bfh, 1, sizeof(BitmapFileHeader), wf);
    fwrite(&bmpf->bih, 1, sizeof(BitmapInfoHeader), wf);

    fseek(wf, bmpf->bfh.pixelArrOffset, SEEK_SET);

    padded_width = image_width * sizeof(Rgb) + image_width * sizeof(Rgb) % 4;
    for (int i = 0; i < image_height; i++) {
        fwrite(bmpf->pixel_array[i], 1, padded_width, wf);
    }

    for (int i = 0; i < image_height; i++)
        free(bmpf->pixel_array[i]);
    free(bmpf->pixel_array);
    fclose(wf);
}


void gradientFrame(Rgb start_color, Rgb end_color, int frame_width, BmpFile *bf) {
    int image_width = (int) bf->bih.width - 1;
    int image_height = (int) bf->bih.height - 1;

    int r_step = (end_color.r - start_color.r) / frame_width;
    int r_rem = (end_color.r - start_color.r) % frame_width;

    int g_step = (end_color.g - start_color.g) / frame_width;
    int g_rem = (end_color.g - start_color.g) % frame_width;

    int b_step = (end_color.b - start_color.b) / frame_width;
    int b_rem = (end_color.b - start_color.b) % frame_width;

    for (int i = 0; i < frame_width; i++) {
        start_color.r += r_step + (i > frame_width - r_rem ? 1 : 0);
        start_color.g += g_step + (i > frame_width - g_rem ? 1 : 0);
        start_color.b += b_step + (i > frame_width - b_rem ? 1 : 0);
        drawLine(0 + i, 0 + i, 0 + i, image_height - i, start_color, bf);
        drawLine(0 + i, image_height - i, image_width - i, image_height - i, start_color, bf);
        drawLine(image_width - i, image_height - i, image_width - i, 0 + i, start_color, bf);
        drawLine(image_width - i, 0 + i, 0 + i, 0 + i, start_color, bf);
    }
}

void stripedFrame(Rgb color1, Rgb color2, int frame_width, BmpFile *bf) {
    int image_width = (int) bf->bih.width - 1;
    int image_height = (int) bf->bih.height - 1;

    Rgb colors[] = {color1, color2};
    for (int i = 0; i < frame_width; i++) {
        drawLine(0 + i, 0 + i, 0 + i, image_height - i, colors[i % 2], bf);
        drawLine(0 + i, image_height - i, image_width - i, image_height - i, colors[i % 2], bf);
        drawLine(image_width - i, image_height - i, image_width - i, 0 + i, colors[i % 2], bf);
        drawLine(image_width - i, 0 + i, 0 + i, 0 + i, colors[i % 2], bf);
    }
}

void wavyFrame(Rgb color, int thickness, BmpFile *bf) {
    int image_width = (int) bf->bih.width;
    int image_height = (int) bf->bih.height;

    for (int x = 0; x < image_width; x++) {
        for (int y = 0; y < thickness; y++) {
            int f_x = (int) fabs(thickness * sin(2.0 / thickness * x));
            if (y <= f_x)
                bf->pixel_array[y][x] = color;
        }
    }

    for (int y = 0; y < image_height; y++) {
        for (int x = (int) image_width - thickness; x < image_width; x++) {
            int f_y = (int) fabs(thickness * sin(2.0 / thickness * y));
            if (image_width - x <= f_y)
                bf->pixel_array[y][x] = color;
        }
    }

    for (int x = 0; x < image_width; x++) {
        for (int y = image_height - thickness; y < image_height; y++) {
            int f_x = image_height - (int) fabs(thickness * sin(2.0 / thickness * x));
            if (y >= f_x)
                bf->pixel_array[y][x] = color;
        }
    }

    for (int y = 0; y < image_height; y++) {
        for (int x = 0; x < thickness; x++) {
            int f_y = (int) fabs(thickness * sin(2.0 / thickness * y));
            if (x <= f_y)
                bf->pixel_array[y][x] = color;
        }
    }
}

