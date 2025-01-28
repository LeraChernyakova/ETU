#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "getopt.h"


int check_correct_copy_coordinates(Area *area, File *file){
	//checking that all coordinates of the copy area are in pictures
	if ((area->start.x < 0) || (area->start.x > file->W-1) || (area->start.y < 0) || (area->start.y > file->H-1) || (area->end.x < 0) || (area->end.x > file->W-1) || (area->end.y < 0) || (area->end.y > file->H-1)){
		printf("\x1b[31mThe specified area goes beyond the boundaries of the picture (min x = 0, min y = 0, max x = %d, max y = %d)\x1b[0m\n", file->W-1, file->H-1);
		return -1;
	}

	//checking the correctness of the entred coordinates of the left upper corner and right lower corner 
	if ((area->start.x > area->end.x) || (area->start.y < area->end.y)){
		printf("\x1b[31mIncorrect coordinates of the left upper corner and the right lower corner (the origin is in the lower left corner)\x1b[0m\n");
		return -1;
	}

	//checking the possibility of inserting a selected area
	if ((area->insert.x < 0) || (area->insert.x > file->W-1) || (area->insert.y < 0) || (area->insert.y > file->H-1) || (area->insert.x + area->w > file->W-1) || (area->insert.y - area->h < 0)){
		printf("\x1b[31mUnable to insert a copied area\x1b[0m\n");
		return -1;
	}

	return 0;
}


Rgb **create_cpy_area(Rgb **arr, Area *area){
	//seting initial coordinates for copying
	int y_start = area->end.y;
	int x_start = area->start.x;

	//copy area
	Rgb **cpy_arr = malloc(area->h * sizeof(Rgb*));
	if (cpy_arr == NULL){
		printf("\x1b[31mh Unable to allocate memmory for copy_arr\x1b[0m\n");
		return NULL;
	}

	for(int i = 0; i < area->h; i++){
		cpy_arr[i] = malloc(area->w * sizeof(Rgb));
		if (cpy_arr[i] == NULL){
			printf("\x1b[31mw Unable to allocate memmory for copy_arr\x1b[0m\n");
			return NULL;
		}

		for (int j = 0; j < area->w; j++){
			cpy_arr[i][j] = arr[y_start+i][x_start+j];
		}
	}

	return cpy_arr;
}


void free_copy_area(Rgb **arr, Area *area){
	for (int i = 0; i < area->h; i++){
		free(arr[i]);
	}
	free(arr);
}


int CopyAreaFunc(Rgb **arr, Area *area, File *file){
	//checking if all flags are passed
	if (!area->flags[0] || !area->flags[1] || !area->flags[2]){
		printf("\x1b[31mNot all necessary flags for coping were passed\x1b[0m\n");
		return -1;
	}
	
	//getting the height and width of the copied area
	area->w = abs(area->end.x - area->start.x) + 1;
	area->h = abs(area->start.y - area->end.y) + 1;

	if (check_correct_copy_coordinates(area, file) == -1){
		return -1;
	}
	
	Rgb **cpy_arr = create_cpy_area(arr, area);

	//checking if the area was copied to an array
	if (cpy_arr == NULL){
		return -1;
	}
	
	//setting initial coordinates for pasting
	int y_insert = area->insert.y - area->h + 1;
	int x_insert = area->insert.x;
	
	//insert area
	for (int i = 0;  i < area->h; i++){
		for (int j = 0; j < area->w; j++){
			arr[y_insert+i][x_insert+j].b = cpy_arr[i][j].b;
			arr[y_insert+i][x_insert+j].g = cpy_arr[i][j].g;
			arr[y_insert+i][x_insert+j].r = cpy_arr[i][j].r;
		}
	}

	//free copy array
	free_copy_area(cpy_arr, area);

	return 0;
}
