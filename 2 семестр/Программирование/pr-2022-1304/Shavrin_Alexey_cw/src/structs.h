#pragma once


typedef struct Point{
	int x;
	int y;
} Point;


typedef struct Rgb{
	unsigned char b;
	unsigned char g;
	unsigned char r;
} Rgb;


typedef struct Configs{
	//hexagon
        int draw_hexagon;	// 0 - false
	//copy
        int copy_area;		// 0 - false
	//switch
        int switch_color;	// 0 - false
	//frame
	int draw_frame;		// 0 - false
	//files
	char *input_file;
	char *output_file;	// default out.bmp
	int bmp_info;		// 0 - do not print
} Configs;


typedef struct Hexagon{
	int flags[5];		//{center, radius, fill, start, end}

	//can be entered instead of center and radius
	Point start;	
	Point end;

	Point center;
	int radius;
	int line_width;		//default 1px
	Rgb line_color;		//default black
	Rgb filling_color;
} Hexagon;


typedef struct Area{
	int flags[3];		//{start, end, insert}
	Point start;	
	Point end;	
	int h;
	int w;		
	Point insert;	
} Area;


typedef struct SwitchColor{
	int flags[2];		//{old, new}
	Rgb old_color;	
	Rgb new_color;	
} SwitchColor;


typedef struct Frame{
	int type;		//default 0;
	int width;		//default 10px;
	Rgb edge_color;		//default white;
	Rgb bg_color;		//default black;
} Frame;


#pragma pack (push, 1)
typedef struct BitmapFileHeader{
	unsigned short signature;
	unsigned int filesize;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int pixelArrOffset;
} BitmapFileHeader;


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
} BitmapInfoHeader;
#pragma pack(pop)


typedef struct File{
	BitmapFileHeader *bmfh;
	BitmapInfoHeader *bmih;
	unsigned int H;
	unsigned int W;
	Rgb **arr;
} File;

