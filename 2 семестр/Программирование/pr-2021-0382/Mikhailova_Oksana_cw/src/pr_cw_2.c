#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#pragma pack(push, 1)
typedef struct BitmapFileHeader{
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
}BitmapFileHeader;

typedef struct BitmapInfoHeader{
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
}BitmapInfoHeader;
#pragma pack(pop)

void printFileHeader(BitmapFileHeader header){
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header){
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width:\t%x (%u)\n", header.width, header.width);
    printf("height:\t%x (%u)\n", header.height, header.height);
    printf("planes:\t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}

typedef struct Rgb{
    unsigned char b;
    unsigned char g;
    unsigned char r;
}Rgb;

void print_help(){
    printf("Программа с CLI по обработке bmp-файла со следующими сведениями:\n");
    printf("\t24 бита на цвет;\n");
    printf("\tбез сжатия;\n");
    printf("\tне используется таблица цветов.\n");
    printf("Первым аргументом введите название файла (путь), который нужно обработать.\n");
    printf("Последним аргументом введите название файла (путь), в который нужно записать результат.\n");
    printf ("Ключи для вызова доступных функций и описание входных данных:\n");
    printf("1) -h/--help: Вывод меню.\n");
    printf("2) -f/--flip: Отражение заданной области.\n"
           "\tПосле ключа введите через запятую координаты левого верхнего угла области, координаты правого нижнего угла области и ось, относительно которой отражать('x' - горизонтальная, 'y' - вертикальная).\n");
    printf("3) -c/--copy: Копирование заданной области.\n"
           "\tПосле ключа введите через запятую координаты левого верхнего угла области-источника, координаты правого нижнего угла области-источника и координаты левого верхнего угла области-назначения.\n");
    printf("4) -p/--pcolor: Заменяет все пиксели одного заданного цвета на другой цвет.\n"
           "\tПосле ключа введите через запятую цвет (значения rgb-компонент), который требуется заменить, и цвет, на который требуется заменить.\n");
    printf("5) -r/--rgb: Фильтр rgb-компонент. Позволяет для всего изображения либо установить в 0 либо установить в 255 значение заданной компоненты.\n"
           "\tПосле ключа введите через запятую значение, в которое нужно установить (0 или 255), и rgb-компоненту ('r', 'g', 'b').\n");
    printf("6) -i/--info: Вывод информации об исходном файле.\n");
}

void flip_area(char* s, int x1, int y1, int x2, int y2, unsigned int W, unsigned int H, Rgb **arr){

    if (x1 > W || y1 > H || x1<0 || y1<0){
        printf("Ошибка (-f/--flip): выбранные координаты левого верхнего угла находятся за пределами изображения.\n");
        return;
    }
    if (x2 > W || y2 > H || x2<0 || y2<0){
        printf("Ошибка (-f/--flip): выбранные координаты правого нижнего угла находятся за пределами изображения.\n");
        return;
    }
    if (x2 < x1){
        printf("Ошибка (-f/--flip): координата х правого нижнего угла должна быть больше координаты х левого верхнего угла).\n");
        return;
    }
    if (y2 > y1){
        printf("Ошибка (-f/--flip): координата y правого нижнего угла должна быть меньше координаты y левого верхнего угла).\n");
        return;
    }
    if (strcmp(s, "x")!=0 && strcmp(s, "y")!=0){
        printf("Ошибка (-f/--flip): выбранная ось недоступна.\n");
        return;
    }

    Rgb a;
    if (strcmp(s, "x")==0) {
        for (int i = y2; i <= (y1+y2)/2; i++) {
            for (int j=x1; j<=x2; j++) {
                a = arr[i][j];
                arr[i][j] = arr[y2+y1-i][j];
                arr[y2+y1-i][j] = a;
            }
        }
    }
    else if (strcmp(s, "y")==0){
        for (int i = y2; i < y1; i++) {
            for (int j = x1; j <= (x1 + x2) / 2; j++) {
                a = arr[i][j];
                arr[i][j] = arr[i][x1 + x2 - j];
                arr[i][x1 + x2 - j] = a;
            }
        }
    }
}

void copy_area(int x1, int y1, int x2, int y2, int x3, int y3, unsigned int W, unsigned int H, Rgb **arr){

    if (x1 > W || y1 > H || x1<0 || y1<0){
        printf("Ошибка (-c/--copy): выбранные координаты левого верхнего угла находятся за пределами изображения.\n");
        return;
    }
    if (x2 > W || y2 > H || x2<0 || y2<0){
        printf("Ошибка (-c/--copy): выбранные координаты правого нижнего угла находятся за пределами изображения.\n");
        return;
    }
    if (x2 < x1){
        printf("Ошибка (-c/--copy): координата х правого нижнего угла должна быть больше координаты х левого верхнего угла).\n");
        return;
    }
    if (y2 > y1){
        printf("Ошибка (-c/--copy): координата y правого нижнего угла должна быть меньше координаты y левого верхнего угла).\n");
        return;
    }
    if (x3 > W || y3 > H || x3<0 || y3<0){
        printf("Ошибка (-c/--copy): выбранные координаты левого верхнего угла области-назначения находятся за пределами изображения.\n");
        return;
    }
    if ((x2-x1)>W-x3 || (y1-y2)>y3){
        printf("Ошибка (-c/--copy): выбранная область-назначения меньше области-источника.\n");
        return;
    }

    int h = y1-y2+1;
    int w = x2-x1+1;
    Rgb** copy = malloc(h*sizeof(Rgb*));
    for (int i=0; i<h; i++){
        copy[i] = malloc(w*sizeof(Rgb));
    }
    int x = 0;
    int y = 0;
    for (int i=y2; i<=y1; i++){
        x=0;
        for (int j=x1; j<=x2; j++){
            copy[y][x] = arr[i][j];
            x++;
        }
        y++;
    }
    int m = 0;
    int n;
    for (int i=y3-y+1; i<=y3; i++) {
        n = 0;
        for (int j = x3; j < x3 + x; j++) {
            arr[i][j] = copy[m][n];
            n++;
        }
        m++;
    }
}

void pixels_color_change(int r1, int g1, int b1, int r2, int g2, int b2, unsigned int H, unsigned int W, Rgb** arr){
    if (r1>255 || r1<0 || g1>255 || g1<0 || b1>255 || b1<0){
        printf("Ошбика (-p/--pcolor): выбранные параметры цвета, который нужно заменить, находятся вне допустимых границ.\n");
        return;
    }
    if (r2>255 || r2<0 || g2>255 || g2<0 || b2>255 || b2<0){
        printf("Ошбика (-p/--pcolor): выбранные параметры цвета, на который нужно заменить, находятся вне допустимых границ.\n");
        return;
    }
    int flag = 1;
    for (int i = 0; i<H; i++){
        for (int j = 0; j<W; j++){
            if (arr[i][j].r == r1 && arr[i][j].g == g1 && arr[i][j].b == b1){
                arr[i][j].r = r2;
                arr[i][j].g = g2;
                arr[i][j].b = b2;
                flag = 0;
            }
        }
    }
    if (flag){
        printf("Ошбика (-p/--pcolor): данное изображение не содержит выбранного цвета.\n");
    }
}

void rgb_filter(char* s, int c, unsigned int H, unsigned int W, Rgb** arr){
    if (c>255 || c<0){
        printf("Ошибка (-r/--rgb): выбранные параметры цвета находятся вне допустимых границ.\n");
        return;
    }
    if (strcmp(s, "r")!=0 && strcmp(s, "g")!=0 && strcmp(s, "b")!=0){
        printf("Ошибка (-r/--rgb): выбранный цвет отсутствует в rgb-компоненте.\n");
        return;
    }
    for (unsigned int i=0; i<H; i++){
        for (unsigned int j=0; j<W; j++){
            if (strcmp(s, "r")==0) {
                arr[i][j].r = c;
            }
            else if (strcmp(s, "g")==0) {
                arr[i][j].g = c;
            }
            else if (strcmp(s, "b")==0) {
                arr[i][j].b = c;
            }
        }
    }

}


int main(int argc, char* argv[]){

    char *opts = "f:c:p:r:ih";
    struct option longOpts[]={
            {"flip", required_argument, NULL, 'f'},
            {"copy", required_argument, NULL, 'c'},
            {"pcolor", required_argument, NULL, 'p'},
            {"rgb", required_argument, NULL, 'r'},
            {"info", no_argument, NULL, 'i'},
            {"help", no_argument, NULL, 'h'},
            {NULL, 0, NULL, 0}
    };

    int opt;
    int longIndex;
    opt = getopt_long(argc, argv, opts, longOpts, &longIndex);

    if (opt == -1){
        print_help();
        return 0;
    }

    char* filename = malloc((strlen(argv[1]))*sizeof(char));
    strcpy(filename, argv[1]);
    char * out_filename = malloc((strlen(argv[argc-1]))*sizeof(char));
    strcpy(out_filename, argv[argc-1]);

    FILE *f = fopen(filename, "rb");
    if (!f){
        if (opt == 'h') {
            print_help();
            return 0;
        }
        else {
            printf("Ошибка при чтении исходного файла.\n");
            return 0;
        }
    }
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    fread(&bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(&bmih, 1, sizeof(BitmapInfoHeader), f);
    if (bmfh.signature != 0x4d42){
        printf("Файл не соотвествует формату bmp. Пожалуйста, выберите другой файл.\n");
        return 0;
    }
    if (bmih.bitsPerPixel != 24){
        printf("Глубина цвета данного файла не 24 пикселя на бит. Пожалуйста, выберите другой файл.\n");
        return 0;
    }
    if (bmih.colorsInColorTable != 0){
        printf("Для данного файла используется таблица цветов. Пожалуйста,выберите другой файл.\n");
        return 0;
    }
    if (bmih.compression != 0){
        printf("Изображение сжатое. Пожалуйста, выберите другой файл.\n");
        return 0;
    }

    unsigned int H = bmih.height;
    unsigned int W = bmih.width;

    Rgb **arr = malloc(H*sizeof(Rgb*));
    for( int i=0; i<H; i++){
        arr[i] = malloc(W*sizeof(Rgb)+(W*3)%4);
        fread(arr[i], 1, W*sizeof(Rgb)+(W*3)%4, f);
    }
    fclose(f);


    while(opt!=-1){
        switch(opt){
            case 'f': {
                char s[50];
                int x1, y1, x2, y2;
                int count = sscanf(optarg, "%d,%d,%d,%d,%s", &x1, &y1, &x2, &y2, s);
                if (count<5){
                    printf("Ошибка (-f/--flip): не хватает аргументов для выполнения функции.\n");
                    break;
                }
                s[1] = '\0';

                flip_area(s, x1, y1, x2, y2, W, H, arr);
                break;
            }
            case 'c': {
                int x1, y1, x2, y2, x3, y3;
                int count = sscanf(optarg, "%d,%d,%d,%d,%d,%d", &x1, &y1, &x2, &y2, &x3, &y3);
                if (count<6){
                    printf("Ошибка (-c/--copy): не хватает аргументов для выполнения функции.\n");
                    break;
                }
                copy_area(x1, y1, x2, y2, x3, y3, W, H, arr);
                break;
            }
            case 'p': {
                int r1, g1, b1, r2, g2, b2;
                int count = sscanf(optarg, "%d,%d,%d,%d,%d,%d", &r1, &g1, &b1, &r2, &g2, &b2);
                if (count<6){
                    printf("Ошибка (-p/--pcolor): не хватает аргументов для выполнения функции.\n");
                    break;
                }
                pixels_color_change(r1, g1, b1, r2, g2, b2, H, W, arr);
                break;
            }
            case 'r': {
                int c;
                char s[50];
                int count = sscanf(optarg, "%d,%s", &c, s);
                if (count<2){
                    printf("Ошибка (-r/--rgb): не хватает аргументов для выполнения функции.\n");
                    break;
                }
                s[1] = '\0';
                rgb_filter(s, c, H, W, arr);
                break;
            }
            case 'i': {
                printFileHeader(bmfh);
                printInfoHeader(bmih);
                break;
            }
            case 'h':{
                print_help();
                break;
            }
            default:{
                printf("Нет такого ключа.\n");
                break;
            }
        }
        opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
    }


    if (strcmp(out_filename, argv[argc-1])!=0){
        printf("Не введено название результирующего файла.\n");
        for (int i=0; i<H; i++){
            free(arr[i]);
        }
        free(arr);
        return 0;
    }

    FILE *ff = fopen(out_filename, "wb");
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmih, 1, sizeof(BitmapInfoHeader), ff);
    unsigned int w = W*sizeof(Rgb)+(W*3)%4;
    for (int i=0; i<H; i++){
        fwrite(arr[i], 1, w, ff);
    }
    fclose(ff);
    for (int i=0; i<H; i++){
        free(arr[i]);
    }
    free(arr);

    return 0;
}
