#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <locale.h>
#include <getopt.h>

#pragma pack (push, 1)
    typedef struct{
        uint16_t signature; // BM BA CI CP IC PT
        uint32_t fileSize;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t pixelArrOffset;
    } BitmapFileHeader;

    typedef struct{
        uint32_t headerSize; // 28(40) for BITMAPINFOHEADER
        uint32_t width;
        uint32_t height;
        uint16_t planes; // must be 1
        uint16_t bitsPerPixel; // 18(24) bits (BGR)
        uint32_t compression; // 0 (no compression)
        uint32_t imageSize;
        uint32_t xPixelsPerMeter;
        uint32_t yPixelsPerMeter;
        uint32_t colorsUsed;
        uint32_t importantColors;
    } BitmapInfoHeader;

    typedef struct{
        uint8_t blue;
        uint8_t green;
        uint8_t red;
    } BGR;

    typedef struct{
        BitmapFileHeader fileHeader;
        BitmapInfoHeader infoHeader;
        BGR** pixelArray;
        uint32_t bytesPerRow;
    } BMP;

#pragma pack(pop)

int readBMP(char* path, BMP* image){
    FILE* inputStream = fopen(path, "rb");
    if(!inputStream){ wprintf(L"Не удаётся открыть файл %hs\n", path); return 0; }

    fread(&(image->fileHeader), 1, sizeof(BitmapFileHeader), inputStream);
    if(image->fileHeader.signature != 0x4d42){ wprintf(L"Неподдерживаемый тип файла\n"); return 0; }

    fread(&(image->infoHeader), 1, sizeof(BitmapInfoHeader), inputStream);
    if(image->infoHeader.headerSize != 40){ wprintf(L"Неподдерживаемая версия BMP. Должен быть BMP Version 3 (Microsoft Windows 3.x / 40 bytes BITMAPINFOHEADER)\n"); return 0; }
    if(image->infoHeader.bitsPerPixel != 24) { wprintf(L"Неподдерживаемая глубина изображения. Должная быть 24 бита\n"); return 0; }
    if(image->infoHeader.compression != 0) { wprintf(L"Сжатие изображения не поддерживается\n"); return 0; }

    uint32_t height = image->infoHeader.height;
    uint32_t width = image->infoHeader.width;
    if(height > 65535 || width > 65535) { wprintf(L"Слишком большое изображение\n"); return 0; }
    uint32_t bytesPerRow = width*sizeof(BGR) + (4 - (width*sizeof(BGR))%4)%4;

    image->bytesPerRow = bytesPerRow;
    image->pixelArray = malloc(height*sizeof(BGR*));
    for(int i = 0; i < height; i++){
        image->pixelArray[i] = malloc(bytesPerRow);
        fread(image->pixelArray[i], 1, bytesPerRow, inputStream);
    }
    fclose(inputStream);
    return 1;
}

BGR createBGR(uint8_t blue, uint8_t green, uint8_t red){
    BGR bgr = {blue, green, red};
    return bgr;
}

void drawRectangleFrame(BMP* image, int16_t x1, int16_t y1, uint16_t x2, uint16_t y2, uint8_t borderWidth, BGR color){
    for(int x = x1 - borderWidth; x <= x2 + borderWidth; x++)
        for(int y = y1 - borderWidth; y <= y2 + borderWidth; y++)
            if(x >= 0 && y >= 0 && x < image->infoHeader.width && y < image->infoHeader.height &&
                ((x <= x1 || x >= x2) || (y <= y1 || y >= y2))) image->pixelArray[y][x] = color;
}

void colorSwap(BMP* image, BGR colorToChange, BGR newColor){
    for(int i = 0; i < image->infoHeader.height; i++)
        for(int j = 0; j < image->infoHeader.width; j++)
            if(!memcmp(&(image->pixelArray[i][j]), &colorToChange, sizeof(BGR))) image->pixelArray[i][j] = newColor;
}

void frame(BMP* image, uint16_t padding, BGR color, uint8_t pattern, BGR patternColor){
    uint32_t newHeight = image->infoHeader.height + 2*padding;
    uint32_t newWidth = image->infoHeader.width + 2*padding;
    uint32_t newBytesPerRow = newWidth*sizeof(BGR) + (4-(newWidth*sizeof(BGR))%4)%4;

    BGR** newPixArr = malloc(newHeight*sizeof(BGR*));

    short a;
    for(int i = 0; i < newHeight; i++){
        newPixArr[i] = calloc(1, newBytesPerRow);
        for(int j = 0; j < newWidth; j++){
            if(i < padding || i >= newHeight-padding || j < padding || j >= newWidth-padding){
                switch (pattern){
                    case 1: //horizaontal lines
                        if(((i > padding && i < newHeight-padding) && (i % padding*2 < padding )) ||
                            ((j > padding && j < newWidth-padding) && (j % padding*2 < padding ))) newPixArr[i][j] = patternColor;
                        else newPixArr[i][j] = color;
                        break;
                    case 2: //waves
                        if((j < padding || j > newWidth - padding) && (i < padding || i > newHeight - padding)){ newPixArr[i][j] = patternColor; break; }
                        a = round((sin((double)j/10) * padding / 2)+padding/2);
                        if((i < a) || (i > newHeight - a)){ newPixArr[i][j] = patternColor; break; }
                        a = round((sin((double)i/10) * padding / 2)+padding/2);
                        if((j < a) || (j > newWidth - a)){ newPixArr[i][j] = patternColor; break; }
                        newPixArr[i][j] = color;
                        break;
                    case 3: //curved lines
                        a = round((sin((double)j/10) * padding / 2)+padding/2);
                        if((j > padding && j < newWidth-padding) && ((abs(i - a) < 3) || (abs(newHeight - i - a) < 3))) newPixArr[i][j] = patternColor;
                        else{
                            a = round((sin((double)i/10) * padding / 2)+padding/2);
                            if((i > padding && i < newHeight-padding) && ((abs(j - a) < 3) || (abs(newWidth - j - a) < 3))) newPixArr[i][j] = patternColor;
                            else newPixArr[i][j] = color;
                        }
                        break;
                    default:
                        newPixArr[i][j] = color;
                        break;
                }
            } 
            else{
                newPixArr[i][j] = image->pixelArray[i-padding][j-padding];
            } 
        }
    }   
    for(int i = 0; i < image->infoHeader.height; i++) free(image->pixelArray[i]);
    free(image->pixelArray);

    image->infoHeader.height = newHeight;
    image->infoHeader.width = newWidth;
    image->bytesPerRow = newBytesPerRow;
    image->pixelArray = newPixArr;
}

void findRectangles(BMP* image, BGR color, BGR borderColor, uint16_t borderWidth){
    BGR** arr = image->pixelArray;
    int count = 0, maxCount = 10;
    uint16_t* coordinates = malloc(maxCount*4*sizeof(uint16_t));
    uint16_t x2, y2; uint8_t sameHeight;
    for(int x = 0; x < image->infoHeader.width-1; x++){
        for(int y = 0; y < image->infoHeader.height-1; y++){
            if(!memcmp(&arr[y][x], &color, sizeof(BGR)) &&
                !memcmp(&arr[y+1][x], &color, sizeof(BGR)) && !memcmp(&arr[y][x+1], &color, sizeof(BGR)) &&
                (x== 0 || memcmp(&arr[y][x-1], &color, sizeof(BGR))) && (y == 0 || memcmp(&arr[y-1][x], &color, sizeof(BGR)))){
                    int width;
                    for(width = x+1; (width != image->infoHeader.width) && !memcmp(&arr[y][width], &color, sizeof(BGR)); width++){
                        if(y > 0 && !memcmp(&arr[y-1][width], &color, sizeof(BGR))){ sameHeight=0; break; }
                    }
                    x2=width-1;
                    sameHeight = 1; y2 = 0;
                    for(int i = x; i <= x2; i++){
                        int height;
                        for(height = y+1; height != image->infoHeader.height && !memcmp(&arr[height][i], &color, sizeof(BGR)); height++){
                            if((i==x && x > 0 && !memcmp(&arr[height][x-1], &color, sizeof(BGR)))|| 
                                (i==x2 && x2 + 1 < image->infoHeader.width && !memcmp(&arr[height][x2+1], &color, sizeof(BGR)))){ sameHeight=0; break; }
                        }
                        if(!sameHeight) break;
                        if(!y2) y2 = height-1;
                        else if(height-1 != y2){ sameHeight = 0; break; }
                    }
                    if(sameHeight){
                        coordinates[count*4] = x;
                        coordinates[count*4+1] = y;
                        coordinates[count*4+2] = x2;
                        coordinates[count*4+3] = y2;
                        if(count++==maxCount){ maxCount+=10; realloc(&coordinates, maxCount*4*sizeof(uint16_t)); }
                    } 
                }
        }
    }
    for(int i = 0; i < count; i++){
        drawRectangleFrame(image, coordinates[4*i]-1, coordinates[4*i+1]-1, coordinates[4*i+2]+1, coordinates[4*i+3]+1, borderWidth, borderColor);
    }
    free(coordinates);
}

void writeBMP(char* path, BMP* image){
    FILE* outputStream = fopen(path, "wb");

    fwrite(&(image->fileHeader), 1, sizeof(BitmapFileHeader), outputStream);
    fwrite(&(image->infoHeader), 1, sizeof(BitmapInfoHeader), outputStream);
    for(int i=0; i<image->infoHeader.height; i++) fwrite(image->pixelArray[i], 1, image->bytesPerRow, outputStream); 

    fclose(outputStream);
}

void printFileInfo(BMP image){
    BitmapFileHeader fileHeader = image.fileHeader;
	printf("signature:\t%x (%hu)\n", fileHeader.signature, fileHeader.signature);
	printf("fileSize:\t%x (%u)\n", fileHeader.fileSize, fileHeader.fileSize);
	printf("reserved1:\t%x (%hu)\n", fileHeader.reserved1, fileHeader.reserved1);
	printf("reserved2:\t%x (%hu)\n", fileHeader.reserved2, fileHeader.reserved2);
	printf("pixelArrOffset:\t%x (%u)\n", fileHeader.pixelArrOffset, fileHeader.pixelArrOffset);
    BitmapInfoHeader infoHeader = image.infoHeader;
    printf("headerSize:\t%x (%u)\n", infoHeader.headerSize, infoHeader.headerSize);
	printf("width:     \t%x (%u)\n", infoHeader.width, infoHeader.width);
	printf("height:    \t%x (%u)\n", infoHeader.height, infoHeader.height);
	printf("planes:    \t%x (%hu)\n", infoHeader.planes, infoHeader.planes);
	printf("bitsPerPixel:\t%x (%hu)\n", infoHeader.bitsPerPixel, infoHeader.bitsPerPixel);
	printf("compression:\t%x (%u)\n", infoHeader.compression, infoHeader.compression);
	printf("imageSize:\t%x (%u)\n", infoHeader.imageSize, infoHeader.imageSize);
	printf("xPixelsPerMeter:\t%x (%u)\n", infoHeader.xPixelsPerMeter, infoHeader.xPixelsPerMeter);
	printf("yPixelsPerMeter:\t%x (%u)\n", infoHeader.yPixelsPerMeter, infoHeader.yPixelsPerMeter);
	printf("colorsInColorTable:\t%x (%u)\n", infoHeader.colorsUsed, infoHeader.colorsUsed);
	printf("importantColorCount:\t%x (%u)\n", infoHeader.importantColors, infoHeader.importantColors);
}

void printHelp(){
    wprintf(L"\n\tbmpedit - программа с CLI для редактирования bmp файлов\n");
    wprintf(L"Поддерживаются только файлы BMP Version 3 (Microsoft Windows 3.x / 40 bytes BITMAPINFOHEADER)\n");
    wprintf(L"с глубиной изображения - 24 бита и без сжатия.\n\n");
	wprintf(L"Формат ввода: ./bmpedit [команда] [имя исходного файла] -[ключ1]/--[ключ1] [аргумент1] ...\n\n");
    wprintf(L"\tКомманды:\n");
    wprintf(L"\tfindrect [имя файла] - поиск и обводка всех залитых прямоугольников заданного цвета.\n");
        wprintf(L"\t\t -c/--color1 [.fffffff/255.255.255] - искомый цвет (HEX или RGB)\n");
        wprintf(L"\t\t -w/--width  [число] - ширина обводки (по умолчанию 0)\n");
        wprintf(L"\t\t -C/--color2 [.fffffff/255.255.255] - цвет обводки (HEX или RGB) (по умолчанию чёрный)\n");
        wprintf(L"\t\t -o/--output [путь] - файл для вывода (по умолчанию исходный файл)\n");
    wprintf(L"\tframe [имя файла] - создание рамки в виде узора.\n");
        wprintf(L"\t\t -c/--color1 [.fffffff/255.255.255] - цвет рамки (HEX или RGB)\n");
        wprintf(L"\t\t -w/--width  [число] - ширина рамки (по умолчанию 0)\n");
        wprintf(L"\t\t -s/--style  [0-3] - узор (0 - (по умолчанию) отсутствует, 1-полосы, 2-волны, 3-кривые линии)\n");
        wprintf(L"\t\t -C/--color2 [.fffffff/255.255.255] - цвет узора (HEX или RGB) (по умолчанию чёрный)\n");
        wprintf(L"\t\t -o/--output [путь] - файл для вывода (по умолчанию исходный файл)\n");
    wprintf(L"\thelp - вывод справки о работе программы.\n");
    wprintf(L"\tinfo [имя файла] - вывод информации об изображении.\n");
    wprintf(L"\tswap [имя файла] - замена всех пикселей одного заданного цвета на другой цвет.\n");
        wprintf(L"\t\t -c/--color1 [.fffffff/255.255.255] - искомый цвет (HEX или RGB)\n");
        wprintf(L"\t\t -C/--color2 [.fffffff/255.255.255] - цвет для замены (HEX или RGB) (по умолчанию чёрный)\n");
        wprintf(L"\t\t -o/--output [путь] - файл для вывода (по умолчанию исходный файл)\n");
}

int text2BGR(char* str, BGR* color){
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

int findKey(char* command, int key, BMP* image, char** output, uint16_t* borderWidth, uint8_t* style, BGR* color1, BGR* color2){
    switch (key){
        case 'c':
            if(!text2BGR(optarg, color1)) return 0;
            break;
        case 'C':
            if(!text2BGR(optarg, color2)) return 0;
            break;
        case 'w':
            if(atoi(optarg) > 65535){ wprintf(L"Задан слишком большой размер рамки\n"); return 0; }
            if(atoi(optarg) < 0){ wprintf(L"Значение размера рамки не может быть меньше 0\n"); return 0; }
            else *borderWidth = atoi(optarg);
            break;
        case 's':
            if(atoi(optarg) > 4 || atoi(optarg) < 0){ wprintf(L"Выбранного стиля не существует\n"); return 0; }
            else *style = atoi(optarg);
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

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "");

    BMP image;
    char* output;
    uint16_t borderWidth = 0;
    uint8_t style = 0;
    BGR color1 = createBGR(0, 0, 0);
    BGR color2 = createBGR(0, 0, 0);

    const struct option borderStruct = {"width", required_argument, NULL, 'w'}; 
    const struct option styleStruct  = {"style", required_argument, NULL, 's'}; 
    const struct option color1Struct = {"color1", required_argument, NULL, 'c'};
    const struct option color2Struct = {"color2", required_argument, NULL, 'C'}; 
    const struct option outputStruct = {"output", required_argument, NULL, 'o'};

    if(argc == 1 || !strcmp(argv[1], "help")) { printHelp(); return 0; }
    else if(argc < 3) { wprintf(L"Не введено имя файла с изображением\n"); return -1; }
    else if(!readBMP(argv[2], &image)) return -1;
    else{
        output = argv[2];
        int key, index; opterr = 0;
        if(!strcmp(argv[1], "info")) printFileInfo(image);
        else if(!strcmp(argv[1], "swap")){
            struct option opts[] = {color1Struct, color2Struct, outputStruct};
            while((key = getopt_long(argc, argv, "c:C:o:", opts, &index)) != -1)
                if(!findKey("swap", key, &image, &output, &borderWidth, &style, &color1, &color2)) return -1;
            colorSwap(&image, color1, color2);
        }
        else if(!strcmp(argv[1], "frame")){
            struct option opts[] = {borderStruct, color1Struct, styleStruct, color2Struct, outputStruct};
            while((key = getopt_long(argc, argv, "c:C:w:s:o:", opts, &index)) != -1)
                if(!findKey("frame", key, &image, &output, &borderWidth, &style, &color1, &color2)) return -1;
            frame(&image, borderWidth, color1, style, color2);
        }
        else if(!strcmp(argv[1], "findrect")){
            struct option opts[] = {borderStruct, color1Struct, color2Struct, outputStruct};
            while((key = getopt_long(argc, argv, "c:C:w:o:", opts, &index)) != -1)
                if(!findKey("findrect", key, &image, &output, &borderWidth, &style, &color1, &color2)) return -1;
            findRectangles(&image, color1, color2, borderWidth);
        }
        else{ wprintf(L"Команды %hs не существует\n", argv[1]); return -1; }
    }

    writeBMP(output, &image);
    for(int i = 0; i < image.infoHeader.height; i++) free(image.pixelArray[i]);
    free(image.pixelArray);
    return 0;
}