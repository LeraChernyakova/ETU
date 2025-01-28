#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdint.h>
#pragma pack (push, 1)

static const char *optString = "hip:o:s:r:c:l:";
char * outputFile  = "out.bmp";
const struct option long_options[] = {
		{"help",no_argument,NULL,'h'},
		{"info",no_argument,NULL,'i'},
		{"output",required_argument,NULL,'o'},
       	{"color",no_argument,NULL,'c'},
        	{"line",no_argument,NULL,'l'},
		{"square_circle",no_argument,NULL,'s'},
		{"rad_circle",no_argument,NULL,'r'},
		{"paint_circle",no_argument,NULL,'p'},
		{NULL,0,NULL,0}
};
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

typedef struct{
    uint8_t b;
    uint8_t g;
    uint8_t r;
}Rgb;

#pragma pack(pop)

Rgb** arr;
unsigned int H;
unsigned int W;
int point_w =-1;
int point_h =-1 ;
int rad =-1;
int thick;
int Ox;
int Oy;
int M;
int N;
int Count = 2;

int chekRGB(int R, int G, int B){
    int flag = 0;
    if ((R<0) || (R>255)){
        flag = 1;
    }
    if ((G<0) || (G>255)){
        flag = 1;
    }
    if ((B<0) || (B>255)){
        flag = 1;
    }
    return flag;
}

void printFileHeader(BitmapFileHeader header){
    printf("BitmapFileHeader:\n");
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header){
    printf("BitmapInfoHeader:\n");
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

void PrintHelp(){
    printf(".........................................................................\n");
    printf("This CLI-enabled program handles images in BMP format,\n");
    printf("uncompressed and 24-bit color.\n");
    printf(".........................................................................\n");	
    printf("Information about possible commands:\t -h,  --help \n");
    printf("\n");
    printf("Image information:\t -i,  --info \n");
    printf("\n");
    printf("Entering the file name to display the result:\t -o,  --output \n");
    printf("( -o filename.bmp) \n");
    printf("Default: out.bmp\n");
    printf("\n");
    printf("Filter RGB-components:\t -c,  --color \n");
    printf("Input requirements:\t replacement color, parameter.\n");
    printf("( -с [r/g/b] [0<k<255] ) \n");
    printf("\n");
    printf("Divide the image into NхM parts:\t -l,  --line\n");
    printf("Input requirements:\t number of horizontal and vertical axes,\n");
    printf("line thickness, color (for each parameter).\n");
    printf("( -l [Ox] [Oy] [thick] [red] [green] [blue] )\n");
    printf("\n");
    printf("Draw a circle inscribed in a square:\t -s,  --square_circle \n");
    printf("Input requirements:\t Coordinates of the upper left (along the x and y axes) \n");
    printf("and lower right (along the x and y axes) corner of the squarer,\n");
    printf("line thickness, color (for each parameter).\n");
    printf("( -s [LVw] [LVh] [PNw] [PNh] [thick] [red] [green] [blue] ) \n");
    printf("\n");
    printf("Draw circle in center and radius:\t -r,  --rad_circle \n");
    printf("Input requirements:\t Сenter coordinates (along the x and y axes) \n");
    printf("radius, line thickness, color (for each parameter).\n");
    printf("( -r [point_w] [point_h] [rad] [thick] [red] [green] [blue] ) \n");
    printf("\n");
    printf("Paint over the circle (if available):\t -p,  --paint_circle \n");
    printf("Input requirements:\t color options.\n");
    printf("( -p [thick] [red] [green] [blue] ) \n");
}

void DrawCircle(int R, int G, int B){
    for(int i=0; i<H; i++){
      for(int j=0; j<W; j++){
           if((j - point_w) * (j - point_w) + (i - point_h) * (i - point_h) - rad * rad > -2 * thick * rad && (j - point_w) * (j - point_w) + (i - point_h) * (i - point_h) - rad * rad < 0 ) {
               arr[i][j].r=R;
               arr[i][j].g=G;
               arr[i][j].b=B;
           }
      }
    }
}

void PaintCircle(int R,  int G, int B){
    for(int i=0; i<H; i++){
    	for(int j=0; j<W; j++){
           if((j - point_w) * (j - point_w) + (i - point_h) * (i - point_h) - rad * rad <= -2 * thick * rad && (j - point_w) * (j - point_w) + (i - point_h) * (i - point_h) - rad * rad < 0 ) {
               arr[i][j].r=R;
               arr[i][j].g =G;
               arr[i][j].b=B;

      }

     }
    }
}

void ChangeColor(char c, int k){
    for(int i=0; i<H; i++){
      for(int j=0; j<W; j++){
           if (c == 'r'){
               arr[i][j].r=k;
           }
           if (c == 'g'){
               arr[i][j].g=k;
           }
           if (c == 'b'){
              arr[i][j].b=k;
           }
       }
     }
}

void DrawLines(int R, int G, int B){
   for(int i=0; i<H; i++){
    	for(int j=0; j<W; j++){
           if(j == N) {
           	for (int l = j - (thick / 2); l < j + (thick / 2) + 1; l++){
		       arr[i][l].r=R;
		       arr[i][l].g=G;
		       arr[i][l].b=B;
               }
               N=N+W/Ox;
           }
    	}
       N=W/Ox;
   }

   for(int j=0; j<W; j++){
    	for(int i=0; i<H; i++){
    	if(i== H - thick)
    	{
    	break;
    	}
           if(i == M) {
           	for (int l = i - (thick / 2) - 1; l < i + (thick / 2); l++){
		       arr[l][j].r=R;
		       arr[l][j].g=G;
		       arr[l][j].b=B;

               }
               M=M+H/Oy;
           }

    	}
    	M=H/Oy;
   }
}


int main(int argc, char ** argv){
        if(argc == 1){
            PrintHelp();
            printf("Please try again\n"); //Ничего нет;
            return 0;
        }
    char * inputFile;
    int opt = 0;//какой аргумент сейчас просматриваем

    int inputFileNameLength = strlen(argv[argc-1]);
    inputFile = malloc(inputFileNameLength * sizeof(char));
    strcpy(inputFile, argv[argc-1]);
    FILE *f = fopen(inputFile, "rb"); //Открывает двоичный файл для чтения
        if (f == NULL){
            printf("Please add a file.\n"); //Нет файла для обработки;
            return 0;
        }
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmif;
    fread(&bmfh,1,sizeof(BitmapFileHeader),f);
    fread(&bmif,1,sizeof(BitmapInfoHeader),f);
 	   if(bmfh.signature!=0x4d42){ //Сигнатура bmp-изображения;
         	   printf("Unsupported image format.\n"); //Изображение не bmp;
                   printf("Try again!\n");
    	       	   return 0;
    	   }
	   if(bmif.bitsPerPixel!=24){ 
            	  printf("The color depth of this image is not supported.\n"); //Изображение глубиной НЕ 24 бита на цвет;
                  printf("Requires 24 bits per color.\n");
		  printf("Try again!\n");
                  return 0;
           }
    	   if(bmif.colorsInColorTable!=0){ 
            	  printf("Please use an uncompressed image.\n"); //Таблица цветов;
		  printf("The color table of this image is not supported.\n");
		  printf("Try again!\n");
                  return 0;
           }

    	   if(bmif.compression!=0){ 
            	  printf("Please use an uncompressed image.\n"); //Изображение сжато;
                  return 0;
           }
	
    H = bmif.height;
    W = bmif.width;
    arr = malloc(H*sizeof(Rgb*));
    for(int i=0; i<H; i++){
        arr[i] = malloc(W * sizeof(Rgb) + (W*3)%4);
        fread(arr[i],1,W * sizeof(Rgb) + (W*3)%4,f);
    }
    int option_index;
    opt = getopt_long(argc, argv, optString, long_options, &option_index ); //Получаем новый аргумент
        if (opt == -1){
            printf("Please add the command.\n"); //Нет команды
            return 0;
        }
    while(opt != -1) {
    	switch (opt){
            case 'h':{
		Count = Count+1;
	        	if(Count>argc){
				printf("The arguments do not match the command.\n");//Данных не хватает для обработки;
                        	return 0;
			}
 
                PrintHelp();
                break;
            }
    	    case 'o':{
    	    	Count = Count+2;
	        	if(Count>argc){
				printf("The arguments do not match the command.\n");//Данных не хватает для обработки;
                        	return 0;
			}
    	  	outputFile = optarg;
    	  	break;
    	    }
    	    case 'i':{
    	    	Count = Count+1;
	        	if(Count>argc){
				printf("The arguments do not match the command.\n");//Данных не хватает для обработки;
                        	return 0;
			}
  		printFileHeader(bmfh);
    		printInfoHeader(bmif);
  		break;
  		    }

            case 'c':{
            	Count = Count+3;
	        	if(Count>argc){
				printf("The arguments do not match the command.\n");//Данных не хватает для обработки;
                        	return 0;
			}
                char colorName;
                int Value;
                int a=0;
                if (option_index!=0){
                    a=1;
                }
                for (int k = -1+a; k<1+a; ++k) {
                    if (k == -1 + a) {
                        colorName = *argv[optind + k];
                    }
                    if (k != -1 + a) {
                        Value = atoi(argv[optind + k]);
                    }
                }
                    if ((colorName != 'r') && (colorName != 'g') && (colorName != 'b')){ 
                        printf("Please enter the color again.\n");//Цвет не принадлижит RGB;
                        return 0;
                    }
                    if ((Value<0) || (Value>255)){
                        printf("Color parameters can take values from 0 to 255.\n");//Параметр цвета вне границ;
                        printf("Try again!\n");
                        return 0;
                    }
                ChangeColor(colorName, Value);
                break;
            }
            case 'l':{
            	Count = Count+7;
	        	if(Count>argc){
				printf("The arguments do not match the command.\n");//Данных не хватает для обработки;
                        	return 0;
			}
                int inletL[6];
                int a=0;
                if (option_index!=0){
                    a=1;
                }
                for (int k = -1+a; k<5+a; ++k){
                    inletL[k + 1 - a] = atoi(argv[optind + k]);
                }
                Ox = inletL[0];
                Oy = inletL[1];
                thick = inletL[2];
                int R=inletL[3];
                int G=inletL[4];
                int B=inletL[5];
                    if (chekRGB(R, G, B)==1){
                        printf("Color parameters can take values from 0 to 255.\n");//Параметр цвета вне границ;
                        printf("Try again!\n");
                        return 0;
                    }
                M= H / Oy;
                N= W / Ox ;
                DrawLines(R, G, B);
                break;
            }
            case 'r':{
            	Count = Count+8;
	        	if(Count>argc){
				printf("The arguments do not match the command.\n");//Цвет не принадлижит RGB;
                        	return 0;
			}
                int inletR[7];
                int a=0;
                if (option_index!=0){
                    a=1;
                }
                for (int k = -1+a; k<6+a; ++k){
                    inletR[k + 1 - a] = atoi(argv[optind + k]);
                }
                point_w=inletR[0];
                point_h=inletR[1];
                rad=inletR[2];
                thick=inletR[3];
                int R=inletR[4];
                int G=inletR[5];
                int B=inletR[6];
                if ((point_w>=W) || (point_h>=H)){
                    printf("The specified coordinates are outside the image.\n"); //Координаты вне изображения
                    printf("Try again!\n");
                    return 0;
                }
                if ((rad>=H) || ((rad>=W))){
                    printf("Radius exceeds image dimensions.\n");//Слишком большой радиус
                    printf("Try again!\n");
                    return 0;
                }
                if (chekRGB(R, G, B)==1){
                    printf("Color parameters can take values from 0 to 255.\n");//Параметр цвета вне границ;
                    printf("Try again!\n");
                    return 0;
                }
                DrawCircle(R, G, B);
                break;
            }
            case 's':{
            	Count = Count+9;
	        	if(Count>argc){
				printf("The arguments do not match the command.\n");//Данных не хватает для обработки;
                        	return 0;
			}
                int inletS[8];
                int a=0;
                if (option_index!=0){
                    a=1;
                }
                for (int k = -1+a; k<8+a; ++k){
                    inletS[k + 1 - a] = atoi(argv[optind + k]);
                }
                int LVw = inletS[0];
                int LVh = inletS[1];
                int PNw = inletS[2];
                int PNh = inletS[3];
                if ((LVw>=W) || (LVh>=H)){ //Верняя левая координатка
                    printf("The specified coordinates are outside the image.\n"); //Координаты вне изображения
                    printf("Try again!\n");
                    return 0;
                }
                if ((PNw>=W) || (PNh>=H)){ //Нижняя левая координатка
                    printf("The specified coordinates are outside the image.\n"); //Координаты вне изображения
                    printf("Try again!\n");
                    return 0;
                }
                if ((PNw - LVw)!=(PNh - LVh)){
                    printf("The entered data does not match the square.\n"); //Введён не квадрат
                    printf("Try again!\n");
                    return 0;
                }

                point_w= (PNw + LVw) / 2 ;
                point_h= (PNh + LVh) / 2;
                rad=(PNh-LVh)/2;
                if ((rad>=H) || ((rad>=W))) {
                    printf("Radius exceeds image dimensions.\n");//Слишком большой радиус
                    printf("Try again!\n");
                    return 0;
                }
                thick=inletS[4];
                int R=inletS[5];
                int G=inletS[6];
                int B=inletS[7];
                if (chekRGB(R, G, B)==1){
                    printf("Color parameters can take values from 0 to 255.\n");//Параметр цвета вне границ;
                    printf("Try again!\n");
                    return 0;
                }
                DrawCircle(R, G, B);
                break;
            }
            case 'p':{
            	Count = Count+4;
	        	if(Count>argc){
				printf("The arguments do not match the command.\n");//Данных не хватает для обработки;
                        	return 0;
			}
                if((point_w == -1) || (point_h == -1) || (rad==-1) ){
                    printf("This option is available only if there is a drawn circle.\n");//Круга нет;
                    printf("Try again!\n");
                    return 0;
                }
                int inletP[3];
                int a = 0;
                if (option_index != 0) {
                    a = 1;
                }
                for (int k = -1 + a; k < 2 + a; ++k) {
                    inletP[k + 1 - a] = atoi(argv[optind + k]);
                }
                int R = inletP[0];
                int G = inletP[1];
                int B = inletP[2];
                if (chekRGB(R, G, B)==1){
                    printf("Color parameters can take values from 0 to 255.\n");//Параметр цвета вне границ;
                    printf("Try again!\n");
                    return 0;
                }
                PaintCircle(R, G, B);
                break;
            }
	    default:{
			break;
	    }
	
        }
        option_index=0;
        opt = getopt_long(argc, argv, optString, long_options,&option_index );
    }

    FILE *ff = fopen(outputFile, "wb");
    bmif.height = H;
    bmif.width = W;
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader),ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader),ff);
    unsigned int w = (W) * sizeof(Rgb) + ((W)*3)%4;
    for(int i=0; i<H; i++){
        fwrite(arr[i],1,w,ff);
    }
    fclose(ff);
    free(arr);
    printf("\n");
    return 0;
}

