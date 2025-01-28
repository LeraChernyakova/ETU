#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <getopt.h>


unsigned int H;
unsigned int W;
char* optstring="hircslo:";
char* outputFile="output.bmp";
char* inputFile;
int flag = 2;

const struct option long_options[] = {
        {"help",no_argument,NULL,'h'},
        {"reflection",no_argument,NULL,'r'},
        {"info",no_argument,NULL,'i'},
        {"copy",no_argument,NULL,'c'},
        {"set",no_argument,NULL,'s'},
        {"lines",no_argument,NULL,'l'},
        {"output",no_argument,NULL,'o'},
        {NULL,0,NULL,0}
};

#pragma pack (push, 1)

typedef struct{
    uint16_t signature;
    uint32_t filesize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixelArrOffset;
} BitmapFileHeader;

#pragma pack(pop)

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

BitmapFileHeader bmfh;
BitmapInfoHeader bmif;

typedef struct
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
} Rgb;

Rgb** arr;

void printFileHeader(BitmapFileHeader header){
    printf("/////////////// BITMAPFILEHEADER information ///////////////\n");
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header){
    printf("/////////////// BITMAPINFOHEADER information ///////////////\n");
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

void setColor (int r,int g,int b,int r1,int g1,int b1)
{
    for (int i=0;i<H;i++)
    {
        for (int j=0;j<W;j++)
        {
            if (arr[i][j].r==r && arr[i][j].g==g && arr[i][j].b==b)
            {
				arr[i][j].r=r1;
				arr[i][j].g=g1;
				arr[i][j].b=b1;
			}
        }
    }
}

void cutPicture(int m,int n,int wid,int r,int g,int b)
{
    int ny=H/n;
    for (int i=1;i<=(n-1);i++)
    {
        for (int j=0;j<W;j++)
        {
            for (int k=-wid/2;k<wid/2+1;k++) {
                arr[i * ny + k][j].b = b;
                arr[i * ny + k][j].g = g;
                arr[i * ny + k][j].r = r;
            }
        }
    }
    int mx=W/m;
    for (int i=1;i<=(m-1);i++)
    {
        for (int j=0;j<H;j++)
        {
            for (int k=-wid/2;k<wid/2+1;k++) {
                arr[j][i*mx+k].b = b;
                arr[j][i*mx+k].g = g;
                arr[j][i*mx+k].r = r;
            }
        }
    }
}

void copySegment(int x1, int y1, int x2, int y2,int xi,int yi)
{
    for (int i=y1;i>=y2;i--)
    {
        for (int j=x1;j<=x2;j++)
        {
            arr[yi+(i-y1)][xi+(j-x1)]=arr[i][j];
        }
    }
}

void pictureReflection(char* way, int xl, int yl, int xr, int yr)
{
    if (strcmp(way,"vertical")==0)
    {
        Rgb tmp;
        for (int i=yl;i>=(yl+yr)/2;i--)
        {
            for (int j=xl;j<=xr;j++)
            {
                tmp=arr[i][j];
                arr[i][j]=arr[yr+(yl-i)][j];
                arr[yr+(yl-i)][j]=tmp;
            }
        }
    }
    if (strcmp(way,"horizontal")==0)
    {
        Rgb tmp;
        for (int j=xl;j<=(xr+xl)/2;j++)
        {
            for (int i=yl;i>=yr;i--)
            {
                tmp=arr[i][j];
                arr[i][j]=arr[i][xr-(j-xl)];
                arr[i][xr-(j-xl)]=tmp;
            }
        }
    }
}

int checkRGB(int r,int g,int b)
{
		if (r<0 || r>255)
		{
			return 0;
		}
		if (g<0 || g>255)
		{
			return 0;
		}
		if (b<0 || b>255)
		{
			return 0;
		}
		return 1;
}

void printHelp()
{
    printf("/////////////////////////////////////////////////////////////////////////\n");
    printf("This program supports uncompressed, 24 bit per color BMP format images.\n");
    printf("Please, read infromation below and run program again.\n");
    printf("/////////////////////////////////////////////////////////////////////////\n");	
    printf("Information about possible commands:\t -h,  --help \n");
    printf("\n");
    printf("Image information:\t -i,  --info \n");
    printf("\n");
    printf("Name of output file:\t -o,  --output \n");
    printf("(Example: -o filename.bmp) \n");
    printf("Default: output.bmp\n");
    printf("\n");
    printf("Change all pixels of one color to another color:\t -s,  --set \n");
    printf("Input requirements:\t replaceable color, replacing color.\n");
    printf("(Example: -s [r] [g] [b] [r1] [g1] [b1] ) \n");
    printf("\n");
    printf("Divide the image into NхM parts:\t -l,  --lines\n");
    printf("Input requirements:\t number of horizontal and vertical segments,line thickness, color (for each parameter).\n");
    printf("(Example: -l [Ox] [Oy] [thick] [red] [green] [blue])\n");
    printf("\n");
    printf("Reflect segment horizontally or vertical:\t -r,  --reflection \n");
    printf("Input requirements:\t axis of reflection, coordinates of left upper and rigth lower corners.\n");
    printf("(Example: -r [axis_of_reflection] [LeftUpperx] [LeftUppery] [RightLowerx] [RightLowery]) \n");
    printf("\n");
    printf("Copy segment of image and insert it in certain place:\t -c,  --copy \n");
    printf("Input requirements:\t coordinates of left upper and right lower corners of copied segment, coordinates of left upper corner of place of insetation.\n");
    printf("(Example: -c [LeftUpperx] [LeftUppery] [RightLowerx] [RightLowery] [LeftUpperxi] [LeftUpperyi]) \n");
    printf("\n");
}

void createOutput()
{
    FILE *ff = fopen(outputFile, "wb");
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader),ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader),ff);
    unsigned int w = (W) * sizeof(Rgb)+((W)*3)%4;
    for(int i=0; i<H; i++){
        fwrite(arr[i],1,w,ff);
    }
    fclose(ff);
    free(arr);
}

int main(int argc, char ** argv){
	if(argc == 1)
	{
		printHelp();
        printf("Please try again\n");
        return 0;
    }
    inputFile=malloc(strlen(argv[argc-1])*sizeof(char));
    strcpy(inputFile,argv[argc-1]);
    FILE *f = fopen(inputFile, "rb");
    if (f == NULL){
            printf("Please add a file.\n");
            return 0;
    }
    fread(&bmfh,1,sizeof(BitmapFileHeader),f);
    fread(&bmif,1,sizeof(BitmapInfoHeader),f);
    if(bmfh.signature!=0x4d42)
    {
		printf("Unsupported image format.\n");
		printf("Try again!\n");
		return 0;
	}
	if(bmif.bitsPerPixel!=24)
	{ 
		printf("The color depth of this image is not supported.\n");
        printf("Requires 24 bits per color.\n");
		printf("Try again!\n");
        return 0;
     }
     if(bmif.colorsInColorTable!=0)
     { 
		printf("The color table of this image is not supported.\n");
		printf("Try again!\n");
		return 0;
     }
	 if(bmif.compression!=0)
	 { 
		printf("Please use an uncompressed image.\n");
	    return 0;
	 }

    H = bmif.height;
    W = bmif.width;

    arr = malloc(H*sizeof(Rgb*));
    for(int i=0; i<H; i++){
        arr[i] = malloc(W * sizeof(Rgb) + (W*3)%4);
        fread(arr[i],1,W * sizeof(Rgb) + (W*3)%4,f);
    }
	fclose(f);
    int option_index;
    int opt=getopt_long(argc,argv,optstring,long_options,&option_index);
    if (opt == -1)
    {
        printf("Please add the command.\n");
		return 0;
    }
    while(opt!=-1)
    {
        switch (opt)
        {
            case 'h':
            {
				flag+=1;
				if (flag>argc)
				{
					printf("The arguments do not match the command.\n");
                    return 0;
				}
                printHelp();
                break;
            }
            case 'i':
            {
				flag+=1;
				if (flag>argc)
				{
					printf("The arguments do not match the command.\n");
                    return 0;
				}
                printFileHeader(bmfh);
                printInfoHeader(bmif);
                break;
            }
            case 'r':
            {
				flag+=6;
				if (flag>argc)
				{
					printf("The arguments do not match the command.\n");
                    return 0;
				}
                char* par[5];
                int long_add=0;
                if (option_index!=0)
                {
                    long_add=1;
                }
                for (int k=-1+long_add;k<4+long_add;++k)
                {
                    par[k+1-long_add]=(argv[optind+k+!long_add]);
                }
                if (strcmp(par[0],"horizontal")!=0 && strcmp(par[0],"vertical")!=0)
                {
					printf("Please use one of avaible way of reflection(horizontal or vertical)\n");
					return 0;
				}
				 if (atoi(par[1])<0 || atoi(par[2])>H-1)
                {
					printf("Coordinates of left upper corner is out of image.\nPlease check parameters of image(use -i(--info)) and try again.\n");
					return 0;
				}
				if (atoi(par[3])>W-1 || atoi(par[4])<0)
				{
					printf("Coordinates of right lower corner is out of image.\nPlease check parameters of image(use -i(--info)) and try again.\n");
					return 0;
				}
				if (atoi(par[1])>atoi(par[3]) || atoi(par[2])<atoi(par[4]))
				{
					printf("Left upper corner is not left upper corner or right lower corner in not right lower corner\nCheck entered coordinates and try again\n");
					return 0;
				}
                //printf("%s %s %s %s %s\n",par[0],par[1],par[2],par[3],par[4]);
                pictureReflection(par[0],atoi(par[1]),atoi(par[2]),atoi(par[3]),atoi(par[4]));
                break;
            }
            case 'c':
            {
				flag+=7;
				if (flag>argc)
				{
					printf("The arguments do not match the command.\n");
                    return 0;
				}
                int par[6];
                int long_add=0;
                if (option_index!=0)
                {
                    long_add=1;
                }
                for (int k=-1+long_add;k<5+long_add;++k)
                {
                    par[k+1-long_add]= atoi(argv[optind+k+!long_add]);
                }
                if (par[0]<0 || par[1]>H-1)
                {
					printf("Coordinates of left upper corner is out of image.\nPlease check parameters of image(use -i(--info)) and try again.\n");
					return 0;
				}
				if (par[2]>W-1 || par[3]<0)
				{
					printf("Coordinates of right lower corner is out of image.\nPlease check parameters of image(use -i(--info)) and try again.\n");
					return 0;
				}
				if (par[4]<0 || par[5]>H-1)
                {
					printf("Coordinates of left upper corner of inserted image is out of default image.\nPlease check parameters of image(use -i(--info)) and try again.\n");
					return 0;
				}
				if (par[0]>par[2] || par[1]<par[3])
				{
					printf("Left upper corner is not left upper corner or right lower corner in not right lower corner\nCheck entered coordinates and try again\n");
					return 0;
				}
				if ((W-par[4]<par[2]-par[0]) || (par[5]<par[1]-par[3]))
				{
					printf("Copied image doesn't fit in entered coordinates\nPlease check parameters of image(use -i(--info)) and try again.\n");
					return 0;
				}
                //printf("%d %d %d %d %d %d\n",par[0],par[1],par[2],par[3],par[4],par[5]);
                copySegment(par[0],par[1],par[2],par[3],par[4],par[5]);
                break;
            }
            case 's':
            {
				flag+=7;
				if (flag>argc)
				{
					printf("The arguments do not match the command.\n");
                    return 0;
				}
                int long_add=0;
                if (option_index!=0)
                {
                    long_add=1;
                }
                int par[6];
                for (int k=-1+long_add;k<5+long_add;++k)
                {
                    par[k+1-long_add]=atoi((argv[optind+k+!long_add]));
                }
                if (checkRGB(par[3],par[4],par[5])==0)
				{
					printf("Please set color components from 0 to 255 and try again.\n");
					return 0;
				}
				if (checkRGB(par[0],par[1],par[2])==0)
				{
					printf("Please set color components from 0 to 255 and try again.\n");
					return 0;
				}
                //printf("%s %s",par[0],par[1]);
                setColor(par[0],par[1],par[2],par[3],par[4],par[5]);
                break;
            }
            case 'l':
            {
				flag+=7;
				if (flag>argc)
				{
					printf("The arguments do not match the command.\n");
                    return 0;
				}
                int long_add=0;
                if (option_index!=0)
                {
                    long_add=1;
                }
                int par[6];
                for (int k=-1+long_add;k<5+long_add;++k)
                {
                    par[k+1-long_add]=atoi((argv[optind+k+!long_add]));
                }
                if (par[0]<0 || par[1]<0)
                {
					printf("Please enter values>0 and try again.\n");
					return 0;
				}
				if (par[0]>30 || par[1]>30)
				{
					printf("Please use values<30 because there is a possibility of error.\n");
					return 0;
				}
				if (par[2]<0 || par[2]>W || par[2]>H)
				{
					
					printf("Please, change value of line's width. For example, use 5 or 10.\n");
					return 0;
				}
				if (checkRGB(par[3],par[4],par[5])==0)
				{
					printf("Please set color components from 0 to 255 and try again.\n");
					return 0;
				}
                //printf("%d %d %d",par[0],par[1],par[2]);
                cutPicture(par[0],par[1],par[2],par[3],par[4],par[5]);
                break;
            }
            case 'o':
            {
				flag+=2;
				if (flag>argc)
				{
					printf("The arguments do not match the command.\n");
                    return 0;
				}
                outputFile=optarg;
                break;
            }
            default:
            {
                break;
            }
        }
        opt=getopt_long(argc,argv,optstring,long_options,&option_index);
    }
    createOutput();
    return 0;
}
