#include "allinfo.h"

int readFile(const char *in, image *img){
    FILE *f = fopen(in,"rb");
    if(!f){
        printf("\n\x1b[31mОшибка! Файл с таким названием не существует. Попробуйте еще раз.\x1b[0m\n");
        return 1;
    }
    fread(&(img->bmfh),1,sizeof(BitmapFileHeader),f);
    fread(&(img->bmih), 1, sizeof(BitmapInfoHeader), f);
    if(img->bmfh.signature != 0x4d42){
        printf("\n\x1b[31mОшибка! Файл данного формата не поддерживается.\x1b[0m\n");
        return 1;
    }
    if(img->bmih.headerSize!=40){
        printf("\n\x1b[31mОшибка! Файл не соотвествует 3 формату BMP.\x1b[0m\n");
        return 1;
    }
    if(img->bmih.bitsPerPixel!=24){
        printf("\n\x1b[31mОшибка! Глубина цветов данного файла не соотвествует 24 пикселя на бит.\x1b[0m\n");
        return 1;
    }
    if(img->bmih.compression){
        printf("\n\x1b[31mОшибка! Данное изображение сжатое.\x1b[0m\n");
        return 1;
    }
    if(img->bmih.colorsInColorTable || img->bmih.importantColorCount){
        printf("\n\x1b[31mОшибка! Для данного файла используется таблица цветов.\x1b[0m\n");
        return 1;
    }
    img->arr = malloc((img->bmih.height)*sizeof(Rgb*) + ((img->bmih.height)*3)%4);
    if(!(img->arr)){
        printf("\n\x1b[31mОшибка! Невозможно выделить память.\x1b[0m\n");
        return 1;
    }
    for(int i=0; i<img->bmih.height; i++){
        img->arr[i] = malloc((img->bmih.width)*sizeof(Rgb) + (3*(img->bmih.width))%4);
        if(!(img->arr[i])){
            printf("\n\x1b[31mОшибка! Невозможно выделить память.\x1b[0m\n");
            return 1;
        }
        fread(img->arr[i],1, (img->bmih.width)*sizeof(Rgb) + (3*(img->bmih.width))%4,f);
    }
    fclose(f);
    return 0;
}

void writeFile(const char *out, int checki, image *img){
    FILE * ff = fopen(out, "wb");

    fwrite(&(img->bmfh), 1, sizeof(BitmapFileHeader), ff);
    fwrite(&(img->bmih), 1, sizeof(BitmapInfoHeader), ff);
    unsigned int w = ((img->bmih).width)*sizeof(Rgb) + (((img->bmih).width*3)%4);
    for(int i=0; i<(img->bmih).height; i++){
        fwrite((img->arr)[i],1,w,ff);
    }
    if (checki == 1){
        printFileHeader(img->bmfh);
        printInfoHeader(img->bmih);
    }
    fclose(ff);
    for(int i=0; i<(img->bmih).height; i++){
        free(img->arr[i]);
    }
    free(img->arr);
}

