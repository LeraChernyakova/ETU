#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <math.h>

#pragma pack(push, 1)

typedef struct{
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
}BitmapFileHeader;

typedef struct{
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

typedef struct{
    unsigned char b;
    unsigned char g;
    unsigned char r;
}Rgb;

typedef struct{
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    Rgb** arr;
}image;


#pragma pack(pop)

int readFile(const char *in, image *img);
void writeFile(const char *out, int checki, image *img);

void printFileHeader(BitmapFileHeader header);
void printInfoHeader(BitmapInfoHeader header);

void printHelp();

void copy_area(int x1, int y1, int x2, int y2, int x3, int y3, unsigned int W, unsigned int H,char* input_str,char* output_str, int checki);
int copy(image *img, int argc, char **argv, int opt, int longIndex);

void flip_area(char* axis, int x1, int y1, int x2, int y2, unsigned int W, unsigned int H, char *input_str, char* output_str, int checki);
int flip(image *img, int argc, char **argv, int opt, int longIndex);

void width(Rgb** arr, int x, int y, int w, int H, int W, unsigned char r, unsigned char g, unsigned char b);
void drawRing(Rgb **arr, unsigned int H, unsigned int W, int R, int x0, int y0, int w, unsigned char r, unsigned char g, unsigned char b);
void drawCircle(Rgb **arr, unsigned int H, unsigned int W, int R, int x0, int y0, int w, unsigned char rl, unsigned char gl, unsigned char bl, unsigned char rf, unsigned char gf, unsigned char bf);
int checkColorLine(Rgb *elem, unsigned char rl, unsigned char gl, unsigned char bl);
int checkColorFill(Rgb *elem, unsigned char rf, unsigned char gf, unsigned char bf);
void ChangeColorFill(Rgb *elem, unsigned char rf, unsigned char gf, unsigned char bf);
void fill(int x, int y, Rgb **arr, unsigned char rl, unsigned char gl, unsigned char bl, unsigned char rf, unsigned char gf, unsigned char bf);
int roundopt(image *img, int argc, char **argv, int opt, int longIndex);

int checkcolor(char *c);
void changecolor(int check, Rgb *c);

void invert_area(int x, int y, int a, int l, unsigned int W, unsigned int H, char *input_str, char* output_str, int checki);
int invert(image *img, int argc, char **argv, int opt, int longIndex);