#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "bmp_info.h"


int read_input_file(Configs *config, File *file, BitmapFileHeader *bmfh, BitmapInfoHeader *bmih){
	FILE *f = fopen(config->input_file, "rb");

	//error checking
	if (f == NULL){
		printf("\x1b[31mUnable to open input file\x1b[0m\n");
		return -1;
	}

	//reading headlines
	fread(bmfh,1,sizeof(BitmapFileHeader),f);
	fread(bmih,1,sizeof(BitmapInfoHeader),f);
	
	//getting height and width
	file->H = bmih->height;
	file->W = bmih->width;

	//pictures reading
	Rgb **arr = malloc(file->H*sizeof(Rgb*));
	
	//error checking
	if (arr == NULL){
		printf("\x1b[31mH Unable to allocate memmory for image\x1b[0m\n");
		return -1;
	}

	for(int i=0; i<file->H; i++){
		arr[i] = malloc(file->W * sizeof(Rgb) + (file->W*3)%4);

		//error checking
		if (arr[i] == NULL){
			printf("\x1b[31mW Unable to allocate memmory for image\x1b[0m\n");
			return -1;
		}
		fread(arr[i],1,file->W * sizeof(Rgb) + (file->W*3)%4,f);
	}
	file->arr = arr;
	fclose(f);
	return 0;
}


int create_output_file(Configs *config, File *file){
	FILE *f = fopen(config->output_file, "wb");

	//error checking
	if (f == NULL){
		printf("\x1b[31mUnable to create output file\x1b[0m\n");
		return -1;
	}

	//writing headlines
	fwrite(file->bmfh, 1, sizeof(BitmapFileHeader),f);
	fwrite(file->bmih, 1, sizeof(BitmapInfoHeader),f);
	unsigned int w = file->W * sizeof(Rgb) + (file->W*3)%4;
	
	for(int i=0; i<file->H; i++){
		fwrite(file->arr[i],1,w,f);
	}

	fclose(f);
	return 0;
}
