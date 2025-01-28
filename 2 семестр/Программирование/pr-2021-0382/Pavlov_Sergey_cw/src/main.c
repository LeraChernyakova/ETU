#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <getopt.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define roundf(x) floor(x + 0.5f)

#pragma pack(push, 1)

typedef struct{
    uint16_t signature;
    uint32_t filesize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixelArrOffset;

} BitmapFileHeader;

typedef struct{

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

typedef struct
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
} Rgb;

#pragma pack(pop)

void printFileHeader(BitmapFileHeader header){
    printf("Signature: \t%x [%u]\n", header.signature, header.signature);
    printf("Filesize: \t%x [%u]\n", header.filesize, header.filesize);
    printf("Reserved1: \t%x [%u]\n", header.reserved1, header.reserved1);
    printf("Reserved2: \t%x [%u]\n", header.reserved2, header.reserved2);
    printf("pixelArrOffSet: \t%x [%u]\n", header.pixelArrOffset, header.pixelArrOffset);
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

// CLI;

void print_help(){

printf("Используйте: myphoto [опции] файл...\n");
printf("\t-h --help\t\t- справочная информация (Вы читаете это)\n");
printf("\t-o --out (название.bmp)\t\t- Устанавливает и сохраняет фотографию под выбраный названием\n");
printf("\t-i --info \t\t- Печать полной информации о bmp файле\n\n");
printf("\t-s --section (x1,y1|x2,y2|толщина|цвет)\t\t- Рисует отрезок по параметрам\n");
printf("\t\t ---> Пример: myphoto --section 2,2,6,6,3,red photo.bmp\n");
printf("\t\t      \tГде цвет имеет тип: [white,black,brown,red,orange,yellow,green,blue,purple,grey]\n\n");
printf("\t-I --inverse (radius x1,y1,R)\t- Инвертировать цвета в заданной окружности\n");
printf("\t\t ---> Пример: myphoto --inverse 50,50,25 photo.bmp\n\n");
printf("\t-с --cut (x1;y1|x2;y2)\t\t- Обрезка изображения\n");
printf("\t\t ---> Пример: myphoto --cut 2,2,3,3 photo.bmp\n");
}
	
struct Configs{
	char* input_file;
	char* out_file;
	_Bool info;
	char* section;
	char* inverse;
	char* cut;
};

// CHECK INPUT FILE;
int is_bmp_file(char* f){
    
    //flags;

    char name_flag = 0;
    char exist_flag = 0;
    char meta_flag = 0;

    // name review:
    if ((f[strlen(f)-4] == '.')&&(f[strlen(f)-3] == 'b')&&(f[strlen(f)-2] == 'm')&&(f[strlen(f)-1] == 'p')){
        name_flag += 1;
    }
    else {
        printf("Ошибка: Неверный формат файла [только .bmp]\n");
        return 0;
    }

    // exist_flag: 

    FILE* tmp = fopen(f,"rb");
    
    if (tmp != NULL){
        exist_flag += 1;
    }
    else {
        printf("Ошибка: указанного файла не существует!\n");
        return 0;
    }
    // meta_flag:

    unsigned short sign;

    fread(&sign,1,2,tmp);

    if (sign == 19778) {
        meta_flag += 1;
    }
    else {
        printf("Ошибка: фото не является не поддерживает .bmp формат\n");
        return 0;
    }

    // answer
    if ((name_flag == 1)&&(exist_flag == 1)&&(meta_flag == 1)) {
        return 1;
        }
    else {
        return 0;
        }

}

// section funcs

struct section_params{
	unsigned int x1;
	unsigned int y1;
	unsigned int x2;
	unsigned int y2;
	unsigned int thick;
	char color[20];
};

struct section_params preprocess_section(char* str){
	struct section_params conf;
	char* tmp;
	sscanf(str,"%d,%d,%d,%d,%s", &conf.x1,&conf.y1,&conf.x2,&conf.y2,tmp);
	sscanf(tmp,"%d,%s",&conf.thick,conf.color);
	free(tmp);
	return conf;
}

Rgb change_color(char* str){

	Rgb ans;

	if (strcmp(str,"blue") == 0){
		ans.b = 255;
		ans.g = 0;
		ans.r = 0;
	}

	else if (strcmp(str,"black") == 0){
		ans.b = 0;
		ans.g = 0;
		ans.r = 0;
	}
	else if (strcmp(str,"white") == 0){
		ans.b = 255;
		ans.g = 255;
		ans.r = 255;
	}
	else if (strcmp(str,"purple") == 0){
		ans.b = 128;
		ans.g = 0;
		ans.r = 128;
	}
	else if (strcmp(str,"purple") == 0){
		ans.b = 128;
		ans.g = 0;
		ans.r = 128;
	}
	else if (strcmp(str,"red") == 0){
		ans.b = 0;
		ans.g = 0;
		ans.r = 255;
	}
	else if (strcmp(str,"yellow") == 0){
		ans.b = 0;
		ans.g = 255;
		ans.r = 255;
	}
	else if (strcmp(str,"green") == 0){
		ans.b = 0;
		ans.g = 255;
		ans.r = 0;
	}
	else if (strcmp(str,"orange") == 0){
		ans.b = 0;
		ans.g = 165;
		ans.r = 255;
	}
	else if (strcmp(str,"brown") == 0){
		ans.b = 19;
		ans.g = 69;
		ans.r = 139;
	}
	return ans;
}

void make_circle(int H, int W,int x0,int y0,Rgb **arr, int radius, Rgb color){
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while(y >= 0) {
		//setPixel(x0 + x, y0 + y);
		arr[y0 + y][x0 + x] = color;
		//setPixel(x0 + x, y0 - y);
		arr[y0 - y][x0 + x] = color;		
		//setPixel(x0 - x, y0 + y);
		arr[y0 + y][x0 - x] = color;
		//setPixel(x0 - x, y0 - y);
		arr[y0 - y][x0 - x] = color;
		error = 2 * (delta + y) - 1;
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
    for(int i = 0; i < H; i++){
		for(int j = 0; j < W; j++)
			if((j-x0)*(j-x0)+(i-x0)*(i-x0)>=radius*radius &&
			(j-x0)*(j-x0)+(i-y0)*(i-y0)<=(radius+3)*(radius+3)) arr[i][j] = color;
	}
    for(int i = 0; i < H; i++)
		for(int j = 0; j < W; j++)
			if((j-x0)*(j-x0)+(i-y0)*(i-y0)<=radius*radius) arr[i][j] = color;
}

void swap(char *a, char *b){
	char t = *a;
	*a = *b;
	*b = t;
}

void make_section(unsigned int H,unsigned int W,Rgb **arr, struct section_params conf){

	Rgb color = change_color(conf.color);
	// размер;
	
	int dx = abs(conf.x2 - conf.x1);
	int dy = abs(conf.y2 - conf.y1);
	int len = MAX(dx,dy);

	if (dy == 0){
		for(int i=conf.x1;i<conf.x2;i++){
			//arr[conf.y1][i] = color;

			make_circle(H,W,conf.y1,i, arr,conf.thick,color);
		}
	}
	else if (dx == 0){
		for(int i=conf.y1;i<conf.y2;i++){
			//arr[i][conf.x1] = color;
			make_circle(H,W,i,conf.x1, arr,conf.thick,color);
		}
	}
	else if (dx >= dy){
		int x = conf.x1;
		int y = conf.y1;
		float koef = (float) dy/dx;

		while(x<=conf.x2+1){
                  //arr[(int) roundf(y)][x] = color;
                  make_circle(H,W,roundf(y),x, arr,conf.thick,color);
				  //printf("X: %d Y: %d X*koef: %f\n", x, y, x*koef);
				  x++;
                  y = x*koef;
            }
		}
	else if(dy > dx){
		int x = conf.x1;
		int y = conf.y1;
		float koef = (float) dy/dx;
		while(y<=conf.y2+1){
                //arr[y][(int) roundf(x)] = color;
				make_circle(H,W,y,roundf(x), arr,conf.thick,color);
                //printf("X: %d Y: %d \n", x, y);
				y++;
				x = y/koef;
		}
	}

}

// cut funcs

struct cut_params{
	int x1;
	int y1;
	int x2;
	int y2;
};


void make_cut(unsigned int H, unsigned int W, Rgb **arr, struct cut_params conf){
	for (int i=conf.x1;i<conf.x2;i++){
		for (int j=conf.y1;j<conf.y2;j++){
			arr[i][j].r = 0;
			arr[i][j].g = 0;
			arr[i][j].b = 0;
		}
	}
}

// inverse funcs;

struct inverse_params{
	int x1;
	int y1;
	int radius;
};

void make_inverse(int H, int W, Rgb **arr, struct inverse_params conf){
    int radius = conf.radius;
	for(int i = 0; i < H; i++)
		for(int j = 0; j < W; j++)
			if((j-conf.x1)*(j-conf.x1)+(i-conf.y1)*(i-conf.y1)<=radius*radius){
				arr[i][j].r = 255 - arr[i][j].r;
				arr[i][j].g = 255 - arr[i][j].g;
				arr[i][j].b = 255 - arr[i][j].b;
			}
}

int main(int argc, char *argv[]){

    // CLI;

	struct Configs param_config = {0,0,0,0,0,0};

	static struct option long_options[] = {
		{"help", 0,0,'h'},
		{"info", 0,0,'i'},
		{"out", 1,0,'o'},
		{"section", 1,0,'s'},
		{"inverse", 1,0,'I'},
		{"cut", 1,0,'c'},
		{0,0,0,0}
	};

	int opt;
	int option_index = 0;
	opterr = 0;
	opt = getopt_long(argc, argv,"hio:s:I:c:", long_options, &option_index);
	

	while (opt!=-1){
		switch (opt)
		{
		case 'h':
			print_help();
			return 0;
		case '?':
			printf("Ошибка: Неверный флаг \"-%c\"\n", optopt);
			print_help();
			return 0;
		case 'o':
			param_config.out_file = optarg;
			break;
		case 'i':
			param_config.info = 1;
			break;
		case 's':
			param_config.section = optarg;
			break;
		case 'I':
			param_config.inverse = optarg;
			break;
		case 'c':
			param_config.cut = optarg;
			break;
		}

	opt = getopt_long(argc, argv,"hio:s:I:c:", long_options, &option_index);
	}

	
	// check for file;

	argc -= optind;
	argv += optind;

	if (is_bmp_file(argv[argc-1]) == 1){
		param_config.input_file = argv[argc-1];
	}
	else{
        printf("Фатальная Ошибка: Укажите название изменяемого файла!\n");
		return 0;
	}

	/*
	printf("->CONFIG[outfile]: (%s)\n", param_config.out_file);
	printf("->CONFIG[info]: (%d)\n", param_config.info);
	printf("->CONFIG[section]: (%s)\n", param_config.section);
	printf("->CONFIG[inverse]: (%s)\n", param_config.inverse);
	printf("->CONFIG[cut]: (%s)\n", param_config.cut);
	printf("->CONFIG[inputfile]: (%s)\n", param_config.input_file);
	
	printf("\n");
	*/
    /* 
     =====   Start of programm; =====
    */

   	// [0] PREmap;

	FILE *f = fopen(param_config.input_file, "rb");
    
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;

    fread(&bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(&bmih, 1, sizeof(BitmapInfoHeader), f);

	unsigned int H = bmih.height;
	unsigned int W = bmih.width;

	// Image data: !!!
	Rgb **arr = malloc(H*sizeof(Rgb*));

	for(int i=0; i<H; i++){
		arr[i] = malloc(W * sizeof(Rgb) + (W*3)%4);
		fread(arr[i],1,W * sizeof(Rgb) + (W*3)%4,f);
	}

    //[1] INFO 

	if (param_config.info == 1) {
		printFileHeader(bmfh);
		printInfoHeader(bmih);

	}
    //[2] Section

	if (param_config.section != 0){

		struct section_params sect_conf = preprocess_section(param_config.section);
		//printf(":: |: %d| |:%d| |%d| |%d| |%d| |%s| \n", sect_conf.x1,sect_conf.y1,sect_conf.x2,sect_conf.y2,sect_conf.thick,sect_conf.color);
		make_section(H, W , arr, sect_conf);
	}

    //[3] Inverse

	if (param_config.inverse != 0){

		struct inverse_params inv_conf;
		sscanf(param_config.inverse,"%d,%d,%d", &inv_conf.x1,&inv_conf.y1,&inv_conf.radius);
		make_inverse(H,W,arr,inv_conf);
	}

    //[4] Cut

	if (param_config.cut != 0){
		struct cut_params lp;
		sscanf(param_config.cut,"%d,%d,%d,%d", &lp.x1,&lp.y1,&lp.y2,&lp.x2);
		make_cut(H, W , arr, lp);
	}

    //[5 - FINAL] Out file
	FILE* ff;

	if (param_config.out_file == 0){
		 ff = fopen(param_config.input_file, "wb");
		 }
	else {
		 ff = fopen(param_config.out_file, "wb");
	}


	fwrite(&bmfh, 1, sizeof(BitmapFileHeader),ff);
	fwrite(&bmih, 1, sizeof(BitmapInfoHeader),ff);
	unsigned int w = (W) * sizeof(Rgb) + ((W)*3)%4;
	for(int i=0; i<H; i++){
		fwrite(arr[i],1,w,ff);
	}
	fclose(ff);
	
	printf("\n");
	
	return 0;
}