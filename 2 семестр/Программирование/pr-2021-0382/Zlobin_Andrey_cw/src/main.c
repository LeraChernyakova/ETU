#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <getopt.h>
#include <cstring>

#pragma pack (push, 1)

typedef struct
{
    uint16_t signature;
    uint32_t filesize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixelArrOffset;
} BitmapFileHeader;

typedef struct
{
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
} DIBHeader;

typedef struct
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;

#pragma pack(pop)





class BmpStruct {
    BitmapFileHeader FHeader;
    DIBHeader IHeader;
    Rgb **ImData;
public:
    BitmapFileHeader getBitmapFileHeader() {
        return this->FHeader;
    }

    void setBitmapFileHeader(BitmapFileHeader a) {
        this->FHeader = a;
    }

    DIBHeader getDIBHeader() {
        return this->IHeader;
    }

    void setDIBHeader(DIBHeader a) {
        this->IHeader = a;
    }

    Rgb **getImData() {
        return this->ImData;
    }

    void setImData(Rgb **a) {
        this->ImData = a;
    }

    BmpStruct *loadBmp(char *filePath) {
        //BmpStruct * newPic = new BmpStruct();

        FILE *f = fopen(filePath, "rb");
        if (f == NULL) {
            return NULL;
        }
        BitmapFileHeader bmfh;
        DIBHeader bmif;
        fread(&bmfh, 1, sizeof(BitmapFileHeader), f);
        fread(&bmif, 1, sizeof(DIBHeader), f);

        unsigned int H = bmif.height;
        unsigned int W = bmif.width;

        Rgb **arr = (Rgb **) malloc(H * sizeof(Rgb *));
        for (int i = 0; i < H; i++) {
            arr[i] = (Rgb *) malloc(W * sizeof(Rgb) + (W * 3) % 4);
            fread(arr[i], 1, W * sizeof(Rgb) + (W * 3) % 4, f);
        }


        this->setBitmapFileHeader(bmfh);
        this->setDIBHeader(bmif);
        this->setImData(arr);

        return this;
        //return newPic;
    }

    BmpStruct *saveBmp(char *filePath) {
        FILE *ff = fopen(filePath, "wb");
        if (ff == NULL) {
            return NULL;
        }
        int H = this->getDIBHeader().height;
        int W = this->getDIBHeader().width;
        BitmapFileHeader bmfh = this->getBitmapFileHeader();
        DIBHeader bmif = this->getDIBHeader();
        fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
        fwrite(&bmif, 1, sizeof(DIBHeader), ff);
        //for(int i=0; i<H; i++){
        //    for(int j=0; j<W; j++)
        //        swap(&(this->getImData())[i][j].r, &(this->getImData())[i][j].g);
        //}
        unsigned int w = (W) * sizeof(Rgb) + (W * 3) % 4;
        for (int i = 0; i < H; i++) {
            fwrite((this->getImData())[i], 1, w, ff);
        }
        fclose(ff);

    }

    BmpStruct *fillObj(int x, int y, Rgb linecolor, Rgb fillcolor) {
        Rgb **pic = this->getImData();
        if (pic[y][x].r == linecolor.r && pic[y][x].g == linecolor.g && pic[y][x].b == linecolor.b) {
            return this;
        }
        pic[y][x].r = fillcolor.r;
        pic[y][x].g = fillcolor.g;
        pic[y][x].b = fillcolor.b;

        if (x - 1 > 0 && x < this->getDIBHeader().width - 1 && y > 0 && y < this->getDIBHeader().height - 1) {
            this->fillObj(x - 1, y, linecolor, fillcolor);
        }
        if (x + 1 > 0 && x < this->getDIBHeader().width - 1 && y > 0 && y < this->getDIBHeader().height - 1) {
            this->fillObj(x + 1, y, linecolor, fillcolor);
        }
        if (x > 0 && x < this->getDIBHeader().width - 1 && y + 1 > 0 && y < this->getDIBHeader().height - 1) {
            this->fillObj(x, y + 1, linecolor, fillcolor);
        }
        if (x > 0 && x < this->getDIBHeader().width - 1  && y - 1 > 0 && y < this->getDIBHeader().height - 1) {
            this->fillObj(x, y - 1, linecolor, fillcolor);
        }

        return this;
    }


    BmpStruct * drawCircle (int x, int y, Rgb color, int r) {
        int a = 0, b = r;
        int delta = 1 - 2 * r;
        int error = 0;
        Rgb ** pic = this->getImData();
        while (b >= a) {
            for (int i = x - a; i < x + a; i++){
                if (i >= 0 && i < this->getDIBHeader().width - 1 && y + b >= 0 && y + b < this->getDIBHeader().height - 1) {
                    pic[y + b][i] = color;
                }
                if (i >= 0 && i < this->getDIBHeader().width - 1 && y - b >= 0 && y - b < this->getDIBHeader().height - 1) {
                    pic[y - b][i] = color;
                }
            }
            for (int i = x - b; i < x + b; i++){
                if (i >= 0 && i < this->getDIBHeader().width - 1 && y + b >= 0 && y + b < this->getDIBHeader().height - 1) {
                    pic[y + a][i] = color;
                }
                if (i >= 0 && i < this->getDIBHeader().width - 1 && y - a >= 0 && y - a < this->getDIBHeader().height - 1) {
                    pic[y - a][i] = color;
                }
            }

            error = 2 * (delta + b) - 1;
            if (delta < 0 && error <= 0) {
                delta += (2 * ++a + 1);
                continue;
            }
            if (delta > 0 && error > 0) {
                delta -= (2 * --b + 1);
                continue;
            }
            delta += 2 * (++a - --b);
        }
        return this;
    }


    BmpStruct * invertColorsInCircle1 (int x, int y, int r) {
        float a = 0, b = r;
        int delta = 1 - 2 * r;
        int error = 0;
        double x1;
        Rgb **pic = this->getImData();
        while (b > 0){
            x1 =round(sqrt(r*r - b*b));
            for (int i = 0; i < (int ) x1; i++){
                pic[(int )(y + b)][(int )(x + x1)].b =255 - pic[(int )(y + b)][(int )(x + x1)].b ;
                pic[(int )(y + b)][(int )(x + x1)].g =255 - pic[(int )(y + b)][(int )(x + x1)].g ;
                pic[(int )(y + b)][(int )(x + x1)].r =255 - pic[(int )(y + b)][(int )(x + x1)].r ;
            }
            b--;
        }
        return this;
    }

    BmpStruct * drawLine(int x1, int y1, int x2, int y2, Rgb color, char thickness) {
        int A = y2 - y1;
        int B = x1 - x2;
        Rgb ** pic = this->getImData();

        int SignA = 0, SignB = 0;
        if (A<0) {
            SignA = -1;
        } else {
            SignA = 1;
        }
        if (B<0){
            SignB = -1;
        } else {
            SignB = 1;
        }
        int f = 0, x = x1, y = y1;
        this->drawCircle(x, y, color, thickness/2);


        if (abs(A) < abs(B)) {
            do {
                f =f + A * SignA;
                if (f > 0) {
                    f = f - B * SignB;
                    y = y + SignA;
                }
                x = x - SignB;
                printf("%d %d\n", x, y);
                this->drawCircle(x, y, color, thickness/2);

            } while (x != x2 || y != y2);
        } else {
            do {
                f = f + B * SignB;
                if (f > 0) {
                    f = f - A * SignA;
                    x = x - SignB;
                }
                y = y + SignA;
                this->drawCircle(x, y, color, thickness/2);

            } while (x != x2 || y != y2);
        }
        return this;
    }

    BmpStruct * drawTriangle (int x1, int y1, int x2, int y2, int x3, int y3, char thickness, Rgb lineColor, bool ifFilled, Rgb fillColor) {


        if (ifFilled) {
            int H = this->getDIBHeader().height;
            int W = this->getDIBHeader().width;
            Rgb black = {0, 0, 0};
            Rgb white = {255, 255, 255};
            Rgb green = {0, 255, 0};
            BmpStruct *bufPic = new BmpStruct();
            Rgb **pic = this->getImData();
            Rgb **arr = (Rgb **) malloc(H * sizeof(Rgb *));
            for (int i = 0; i < H; i++) {
                arr[i] = (Rgb *) malloc(W * sizeof(Rgb) + (W * 3) % 4);
                for (int j = 0; j < W; j++) {
                    arr[i][j].g = white.g;
                    arr[i][j].r = white.r;
                    arr[i][j].b = white.b;
                }
            }
            bufPic->setDIBHeader(this->getDIBHeader());
            bufPic->setBitmapFileHeader(this->getBitmapFileHeader());
            bufPic->setImData(arr);
            bufPic->drawLine(x1, y1, x2, y2, black, 2);
            bufPic->drawLine(x2, y2, x3, y3, black, 2);
            bufPic->drawLine(x3, y3, x1, y1, black, 2);
            bufPic->fillObj((x1+x2+x3)/3, (y1 + y2 + y3)/3, black, black);

            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    if (arr[i][j].b == black.b && arr[i][j].g == black.g && arr[i][j].r == black.r) {

                            pic[i][j].b = fillColor.b;
                            pic[i][j].g = fillColor.g;
                            pic[i][j].r = fillColor.r;

                }
            }
        }
            this->drawLine(x1, y1, x2, y2, lineColor, thickness);
            this->drawLine(x2, y2, x3, y3, lineColor, thickness);
            this->drawLine(x3, y3, x1, y1, lineColor, thickness);
            return this;

        }
    }

    BmpStruct * invertColorsInCircle(int x, int y, int r) {
        int a = 0, b = r;
        int delta = 1 - 2 * r;
        int error = 0;
        int b_prev = b;
        int a_prev = a;
        Rgb ** pic = this->getImData();
        while (b >= a - 1) {
            for (int i = x - a + 1; i < x + a - 1; i++){
                if (i >= 0 && i < this->getDIBHeader().width && y + b >= 0 && y + b < this->getDIBHeader().height && (b_prev != b)) {
                    pic[y + b_prev][i].b = 255 - pic[y + b_prev][i].b;
                    pic[y + b_prev][i].g = 255 - pic[y + b_prev][i].g;
                    pic[y + b_prev][i].r = 255 - pic[y + b_prev][i].r;
                }
                if (i >= 0 && i < this->getDIBHeader().width && y - b >= 0 && y - b < this->getDIBHeader().height && (b_prev != b)) {
                    pic[y - b_prev][i].b = 255 - pic[y - b_prev][i].b;
                    pic[y - b_prev][i].g = 255 - pic[y - b_prev][i].g;
                    pic[y - b_prev][i].r = 255 - pic[y - b_prev][i].r;
                }
            }
            for (int i = x - b; i < x + b; i++){
                if (i >= 0 && i < this->getDIBHeader().width && y + a >= 0 && y + a < this->getDIBHeader().height && (a_prev != a)) {
                    pic[y + a_prev][i].r = 255 - pic[y + a_prev][i].r;
                    pic[y + a_prev][i].g = 255 - pic[y + a_prev][i].g;
                    pic[y + a_prev][i].b = 255 - pic[y + a_prev][i].b;
                }
                if (i >= 0 && i < this->getDIBHeader().width && y - a >= 0 && y - a < this->getDIBHeader().height && (a_prev != a)) {
                    pic[y - a_prev][i].r = 255 - pic[y - a_prev][i].r;
                    pic[y - a_prev][i].g = 255 - pic[y - a_prev][i].g;
                    pic[y - a_prev][i].b = 255 - pic[y - a_prev][i].b;
                }
            }
            b_prev = b;
            a_prev = a;
            error = 2 * (delta + b) - 1;
            if (delta < 0 && error <= 0) {
                delta += (2 * ++a + 1);
                continue;
            }
            if (delta > 0 && error > 0) {
                delta -= (2 * --b + 1);
                continue;
            }
            delta += 2 * (++a - --b);
        }
        for (int i = x - r; i < x + r; i++){
            pic[y][i].r = 255 - pic[y][i].r;
            pic[y][i].g = 255 - pic[y][i].g;
            pic[y][i].b = 255 - pic[y][i].b;
        }
        return this;
    }

    BmpStruct * cutImg(int x1, int y1, int x2, int y2) {
        BmpStruct * newImg = new BmpStruct();
        uint32_t newWidth = abs(x2 - x1);
        uint32_t newHeight = abs(y2 - y1);
        uint32_t newBytesPerRow = newWidth*sizeof(Rgb) + (4-(newWidth*sizeof(Rgb))%4)%4;
        BitmapFileHeader newHeader = this->getBitmapFileHeader();
        DIBHeader newDIB = this->getDIBHeader();
        newDIB.width = newWidth;
        newDIB.height = newHeight;
        Rgb ** oldPic = this->getImData();
        Rgb **newPic = (Rgb**) malloc(newHeight * sizeof(Rgb*));
        for(int i=0; i<newHeight; i++){
            newPic[i] =(Rgb*) calloc(1, newBytesPerRow);

            for (int j = 0; j < newWidth; j++) {
                newPic[i][j].r = oldPic[i][j].r;
                newPic[i][j].g = oldPic[i][j].g;
                newPic[i][j].b = oldPic[i][j].b;
            }
        }
        newImg->setBitmapFileHeader(newHeader);
        newImg->setDIBHeader(newDIB);
        newImg->setImData(newPic);
        return newImg;
    }



    void printFileInfo(){
        BitmapFileHeader fileHeader = this->getBitmapFileHeader();
        printf("signature:\t%x (%hu)\n", fileHeader.signature, fileHeader.signature);
        printf("fileSize:\t%x (%u)\n", fileHeader.filesize, fileHeader.filesize);
        printf("reserved1:\t%x (%hu)\n", fileHeader.reserved1, fileHeader.reserved1);
        printf("reserved2:\t%x (%hu)\n", fileHeader.reserved2, fileHeader.reserved2);
        printf("pixelArrOffset:\t%x (%u)\n", fileHeader.pixelArrOffset, fileHeader.pixelArrOffset);
        DIBHeader infoHeader = this->getDIBHeader();
        printf("headerSize:\t%x (%u)\n", infoHeader.headerSize, infoHeader.headerSize);
        printf("width:     \t%x (%u)\n", infoHeader.width, infoHeader.width);
        printf("height:    \t%x (%u)\n", infoHeader.height, infoHeader.height);
        printf("planes:    \t%x (%hu)\n", infoHeader.planes, infoHeader.planes);
        printf("bitsPerPixel:\t%x (%hu)\n", infoHeader.bitsPerPixel, infoHeader.bitsPerPixel);
        printf("compression:\t%x (%u)\n", infoHeader.compression, infoHeader.compression);
        printf("imageSize:\t%x (%u)\n", infoHeader.imageSize, infoHeader.imageSize);
        printf("xPixelsPerMeter:\t%x (%u)\n", infoHeader.xPixelsPerMeter, infoHeader.xPixelsPerMeter);
        printf("yPixelsPerMeter:\t%x (%u)\n", infoHeader.yPixelsPerMeter, infoHeader.yPixelsPerMeter);
    }
};


void printHelp(){
    wprintf(L"\n\tbmpedit - программа с CLI для редактирования bmp файлов\n");
    wprintf(L"Поддерживаются только файлы BMP Version 3 (Microsoft Windows 3.x / 40 bytes BITMAPINFOHEADER)\n");
    wprintf(L"с глубиной изображения - 24 бита и без сжатия.\n\n");
    wprintf(L"Формат ввода: ./bmpedit [команда] [имя исходного файла] -[ключ1]/--[ключ1] [аргумент1] ...\n\n");
    wprintf(L"\tКомманды:\n");
    wprintf(L"\tdrawLine [имя файла] - рисует линию по координатам начальной и конечной точки \n");
    wprintf(L"\t\t -a/--x1  [число] - координата x начальной точки\n");
    wprintf(L"\t\t -A/--y1  [число] - координата y начальной точки\n");
    wprintf(L"\t\t -b/--x2  [число] - координата x конечной точки\n");
    wprintf(L"\t\t -B/--y2  [число] - координата y конечной точки\n");
    wprintf(L"\t-t/--thickness [число] - толщина линии\n");
    wprintf(L"\t\t -o/--output [путь] - файл для вывода (по умолчанию исходный файл)\n");
    wprintf(L"\tdrawTriangle [имя файла] - рисует треугольник по координатам его вершин \n");
    wprintf(L"\t\t -a/--x1  [число] - координата x 1 вершины\n");
    wprintf(L"\t\t -A/--y1  [число] - координата y 1 вершины\n");
    wprintf(L"\t\t -b/--x2  [число] - координата x 2 вершины\n");
    wprintf(L"\t\t -B/--y2  [число] - координата y 2 вершины\n");
    wprintf(L"\t\t -с/--x3  [число] - координата x 3 вершины\n");
    wprintf(L"\t\t -С/--y3  [число] - координата y 3 вершины\n");
    wprintf(L"\t\t -f/--color [.fffffff/255.255.255] - цвет заливки (HEX или RGB)\n");
    wprintf(L"\t\t -l/--lineColor [.fffffff/255.255.255] - цвет сторон (HEX или RGB)\n");
    wprintf(L"\t-p/--isFilled [true / false] - необходимо ли выполнять заливку\n");
    wprintf(L"\t-t/--thickness [число] - толщина стороны\n");
    wprintf(L"\t\t -o/--output [путь] - файл для вывода (по умолчанию исходный файл)\n");
    wprintf(L"\tcutImg [имя файла] - обрезает изображение по координатом нижнего левого и правого верхнего угла\n");
    wprintf(L"\t\t -a/--x1  [число] - координата x нижнего левого угла\n");
    wprintf(L"\t\t -A/--y1  [число] - координата y нижнего левого угла\n");
    wprintf(L"\t\t -b/--x2  [число] - координата x правого верхнего угла\n");
    wprintf(L"\t\t -B/--y2  [число] - координата y правого верхнего угла\n");
    wprintf(L"\t\t -o/--output [путь] - файл для вывода (по умолчанию исходный файл)\n");
    wprintf(L"\tinvertColors [имя файла] - инвертирует цвета в окружности\n");
    wprintf(L"\t\t -a/--x1  [число] - координата x нижнего левого угла квадрата, в который вписана окружность\n");
    wprintf(L"\t\t -A/--y1  [число] - координата y нижнего левого угла квадрата, в который вписана окружность\n");
    wprintf(L"\t\t -b/--x2  [число] - координата x правого верхнего угла квадрата, в который вписана окружность\n");
    wprintf(L"\t\t -B/--y2  [число] - координата y правого верхнего угла квадрата, в который вписана окружность\n");
    wprintf(L"\t\t", "или\n");
    wprintf(L"\t\t -a/--x1  [число] - координата x центра окружности\n");
    wprintf(L"\t\t -A/--y1  [число] - координата y центра окружности\n");
    wprintf(L"\t\t -r/--r  [число] - радиус окружности\n");
    wprintf(L"\t\t -o/--output [путь] - файл для вывода (по умолчанию исходный файл)\n");
}
Rgb createBGR(uint8_t blue, uint8_t green, uint8_t red){
    Rgb bgr = {blue, green, green};
    return bgr;
}

int text2BGR(char* str, Rgb* color){
    int16_t red = -1, green = -1, blue = -1;
    if(str[0] == '.' && strlen(str) == 7 && strspn(&str[1], "0123456789aAbBcCdDeEfF") == 6){
        sscanf(str, ".%2x%2x%2x", &red, &green, &blue);
        sscanf(str, ".%2x%2x", &red, &green);
        sscanf(str, ".%2x", &red);
    }else if(strlen(str) >= 5 && strlen(str) <= 11){
        sscanf(str, "%d.%d.%d", &red, &green, &blue);
        sscanf(str, "%d.%d", &red, &green);
        sscanf(str, "%d", &red);
    }
    if(red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255){
        wprintf(L"Введён некорректный цвет\n"); return 0;
    }else *color = createBGR(blue, green, red);
    return 1;
}

int findKey(char* command, int key, BmpStruct * image, char** output, int *a, int *A, int *b, int *B, int *c, int *C, int * r, int * thickness, bool * isFilled, Rgb * color, Rgb * lineColor){

    switch (key) {
        case 'a':
            if(atoi(optarg) > 65535){ wprintf(L"Задана слишком большая координата x1\n"); return 0; }
            if(atoi(optarg) < 0){ wprintf(L"Координата x1 не может быть меньше 0\n"); return 0; }
            else *a = atoi(optarg);
            break;
        case 'A':
            if(atoi(optarg) > 65535){ wprintf(L"Задана слишком большая координата y1\n"); return 0; }
            if(atoi(optarg) < 0){ wprintf(L"Координата y1 не может быть меньше 0\n"); return 0; }
            else *A = atoi(optarg);
        case 'b':
            if(atoi(optarg) > 65535){ wprintf(L"Задана слишком большая координата x2\n"); return 0; }
            if(atoi(optarg) < 0){ wprintf(L"Координата x2 не может быть меньше 0\n"); return 0; }
            else *b = atoi(optarg);
            break;
        case 'B':
            if(atoi(optarg) > 65535){ wprintf(L"Задана слишком большая координата y2\n"); return 0; }
            if(atoi(optarg) < 0){ wprintf(L"Координата y2 не может быть меньше 0\n"); return 0; }
            else *B = atoi(optarg);
            break;
        case 'c':
            if(atoi(optarg) > 65535){ wprintf(L"Задана слишком большая координата x3\n"); return 0; }
            if(atoi(optarg) < 0){ wprintf(L"Координата x3 не может быть меньше 0\n"); return 0; }
            else *c = atoi(optarg);
            break;
        case 'C':
            if(atoi(optarg) > 65535){ wprintf(L"Задана слишком большая координата y3\n"); return 0; }
            if(atoi(optarg) < 0){ wprintf(L"Координата y3 не может быть меньше 0\n"); return 0; }
            else *C = atoi(optarg);
            break;

        case 'r':
            if(atoi(optarg) > 65535){ wprintf(L"Задан слишком большой радиус\n"); return 0; }
            if(atoi(optarg) < 0){ wprintf(L"Радиус не может быть меньше 0\n"); return 0; }
            else *r = atoi(optarg);
            break;
        case 't':
            if(atoi(optarg) > 65535){ wprintf(L"Задана слишком большая толщина\n"); return 0; }
            if(atoi(optarg) < 0){ wprintf(L"Толщина не может быть меньше 0\n"); return 0; }
            else *thickness = atoi(optarg);
            break;
        case 'i':
            if (strcmp(optarg, "true")) {
                *isFilled = true;
            } else {
                *isFilled = false;
            }
        case 'l':
            if(!text2BGR(optarg, lineColor)) return 0;
            break;
        case 'f':
            if(!text2BGR(optarg, color)) return 0;
            break;
        case 'o':
            if(strlen(optarg) < 4 || memcmp(".bmp", optarg + strlen(optarg) - 4, 4)) strcat(optarg, ".bmp");
            *output = optarg;
            break;
        default:
            wprintf(L"Найден неопознанный ключ для комманды \"%hs\"\n", command); return 0;
            break;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    BmpStruct *pic = new BmpStruct();

    setlocale(LC_ALL, "");

    int a = -1, A = -1, b = -1, B = -1, c = -1, C = -1, r = 2, thickness = 2;
    bool isFilled = false;
    char *output;
    uint16_t borderWidth = 0;
    uint8_t style = 0;
    Rgb color = {0, 0, 0};
    Rgb lineColor = {0, 0, 0};

    const struct option x1Struct = {"x1", required_argument, NULL, 'a'};
    const struct option y1Struct = {"y1", required_argument, NULL, 'A'};
    const struct option x2Struct = {"x2", required_argument, NULL, 'b'};
    const struct option y2Struct = {"y2", required_argument, NULL, 'B'};
    const struct option x3Struct = {"x3", required_argument, NULL, 'c'};
    const struct option y3Struct = {"y3", required_argument, NULL, 'C'};
    const struct option rStruct = {"r", required_argument, NULL, 'r'};
    const struct option thicknessStruct = {"thicknessStruct", required_argument, NULL, 't'};
    const struct option lineColorStruct = {"lineColor", required_argument, NULL, 'l'};
    const struct option fillColorStruct = {"fillColor", required_argument, NULL, 'f'};
    const struct option painting = {"isFilled", required_argument, NULL, 'p'};
    const struct option outputStruct = {"output", required_argument, NULL, 'o'};

    if (argc == 1 || !strcmp(argv[1], "help")) {
        printHelp();
        return 0;
    }
    else if (argc < 3) {
        wprintf(L"Не введено имя файла с изображением\n");
        return -1;
    }
    else if (pic->loadBmp(argv[2]) == NULL) return -1;
    else {
        output = argv[2];
        int key, index = 0;
        opterr = 0;
        if (!strcmp(argv[1], "info")) pic->printFileInfo();
        else if (!strcmp(argv[1], "drawLine")) {
            a = -1; A = -1; b = -1; B = -1; r = -1;
            struct option opts[] = {x1Struct, y1Struct, x2Struct, y2Struct, thicknessStruct, lineColorStruct,
                                    outputStruct};
            while ((key = getopt_long(argc, argv, "a:A:b:B:t:l:o:", opts, &index)) != -1) {
                if (!findKey("drawLine", key, pic, &output, &a, &A, &b, &B, &c, &C, &r, &thickness, &isFilled, &color,
                             &lineColor))
                    return -1;

            }
            if (a != -1 && A != -1 && b != -1 && B != -1) {
            pic->drawLine(a, A, b, B, lineColor, thickness);
            pic->saveBmp(output);
            } else {
                wprintf(L"Задайте корректные координаты\n"); return -1; }
        }else if(!strcmp(argv[1], "сutImg")){
            a = -1; A = -1; b = -1; B = -1; r = -1;
                struct option opts[] = {x1Struct, y1Struct, x2Struct, y2Struct, outputStruct};
                while((key = getopt_long(argc, argv, "a:A:b:B:o:", opts, &index)) != -1)
                    if(!findKey("сutImg", key, pic, &output, &a, &A, &b, &B, &c, &C, &r, &thickness, &isFilled, &color, &lineColor)) return -1;
            if (a != -1 && A != -1 && b != -1 && B != -1) {
                pic->cutImg(a, A, b, B);
                pic->saveBmp(output);
            } else {
                 wprintf(L"Задайте корректные координаты\n"); return -1; }
        }

            else if(!strcmp(argv[1], "invertColors")){
                struct option opts[] = {x1Struct, x2Struct, y1Struct, y2Struct, rStruct, outputStruct};
                a = -1; A = -1; b = -1; B = -1; r = -1;
                while((key = getopt_long(argc, argv, "a:A:b:B:r:o:", opts, &index)) != -1)
                    if(!findKey("invertColors", key, pic, &output, &a, &A, &b, &B, &c, &C, &r, &thickness, &isFilled, &color, &lineColor)) return -1;
                if (a != -1 && A != -1 && r != -1) {
                    pic->invertColorsInCircle(a, A, r);
                    pic->saveBmp(output);
                } else {
                    if (a != -1 && A != -1 && b != -1 && B != -1) {
                        pic->invertColorsInCircle((a + A) / 2, (b + B) / 2, abs(a - A) / 2);
                        pic->saveBmp(output);
                    } else {
                         wprintf(L"Задайте корректные координаты\n"); return -1;
                    }
                }

            }
        else if(!strcmp(argv[1], "drawTriangle")){
            struct option opts[] = {x1Struct, x2Struct, x3Struct, y1Struct, y2Struct, y3Struct, lineColorStruct, fillColorStruct, thicknessStruct, painting, outputStruct};
            while((key = getopt_long(argc, argv, "a:A:b:B:c:C:t:p:f:l:o:", opts, &index)) != -1)
                if(!findKey("drawTriangle", key, pic, &output, &a, &A, &b, &B, &c, &C, &r, &thickness, &isFilled, &color, &lineColor)) return -1;
            if (a != -1 && A != -1 && b != -1 && B != -1, c != -1 && C != -1 && thickness != 0) {
                pic->drawTriangle(a, A, b, B, c, C, thickness, lineColor, isFilled, color);
                pic->saveBmp(output);
            }else{ wprintf(L"Команды %hs не существует\n", argv[1]); return -1; }
        }

        delete pic;
            return 0;
        }
    }
