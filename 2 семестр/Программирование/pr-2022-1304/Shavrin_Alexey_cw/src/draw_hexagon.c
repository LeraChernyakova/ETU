#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "getopt.h"
#include "structs.h"
#include "draw_common_func.h"


void hexagon_flood_fill(int x, int y, Rgb **arr, Rgb *new_color, Rgb *boarder_color){
	set_pixel(&arr[y][x], new_color);

	//checking for boarder color or already filled
	if (!is_check_color(&arr[y][x+1], boarder_color) && !is_check_color(&arr[y][x+1], new_color)){
		hexagon_flood_fill(x+1, y, arr, new_color, boarder_color);
	}
	if (!is_check_color(&arr[y][x-1], boarder_color) && !is_check_color(&arr[y][x-1], new_color)){
		hexagon_flood_fill(x-1, y, arr, new_color, boarder_color);
	}
	if (!is_check_color(&arr[y+1][x], boarder_color) && !is_check_color(&arr[y+1][x], new_color)){
		hexagon_flood_fill(x, y+1, arr, new_color, boarder_color);
	}
	if (!is_check_color(&arr[y-1][x], boarder_color) && !is_check_color(&arr[y-1][x], new_color)){
		hexagon_flood_fill(x, y-1, arr, new_color, boarder_color);
	}
}


void get_hexpoints(int x, int y, int r, Rgb **arr, Point *points_arr){
	double angle = 0;	//start angle
	unsigned int n = 6;	//count pick
	for (int i = 0; i < n+1; i++){
		points_arr[i].x = x + r * cos(angle*M_PI/180);
		points_arr[i].y = y + r * sin(angle*M_PI/180);
		angle += 360.0/n;
	}	
}


int is_correct_hex_coordinates(Hexagon *hexagon, File *file){
	int H = (hexagon->radius + hexagon->line_width) * sqrt(3) / 2;
	if (hexagon->center.x < 0 || hexagon->center.x > file->W-1 || hexagon->center.y < 0 || hexagon->center.y > file->H-1){
		printf("\x1b[31mCenter is not in a picture.\x1b[0m\n");
		return 0;
	}

	if (hexagon->center.x + hexagon->radius + hexagon->line_width > file->W-1 || hexagon->center.x - hexagon->radius - hexagon->line_width < 0){
		printf("\x1b[31mHexagon is not fit in width.\x1b[0m\n");
		return 0;
	}

	if (hexagon->center.y + H > file->H-1 || hexagon->center.y - H < 0){
		printf("\x1b[31mHexagon is not fit in height.\x1b[0m\n");
		return 0;
	}

	return 1;
}


int transformation(Hexagon *hexagon){
	//getting the sides of a rectangle
	int a = (hexagon->end.x - hexagon->start.x);
	int b = (hexagon->start.y - hexagon->end.y);

	//check if it's a square
	if (a != b){
		printf("\x1b[31mThese are not square coordinates\x1b[0m\n");
		return -1;
	}

	//conversion to base data
	hexagon->center.x = hexagon->end.x - a/2;
	hexagon->center.y = hexagon->start.y - b/2;
	hexagon->radius = (int)(hexagon->end.x - hexagon->center.x)-hexagon->line_width;
}


int DrawHexagon(Hexagon *hexagon, Rgb **arr, File *file){
	//checking if another flags are passed
	if (hexagon->flags[3] && hexagon->flags[4]){
		if (transformation(hexagon) == -1){
			return -1;
		}
		hexagon->flags[0] = 1;
		hexagon->flags[1] = 1;
		hexagon->flags[3] = 1;
		hexagon->flags[4] = 1;
	}

	//checking if all flags are passed
	if (!hexagon->flags[0] || !hexagon->flags[1]){
		printf("\x1b[31mNot all necessary flags for draw hexagon were passed\x1b[0m\n");
		return -1;
	}

	//checking correct coordinates
	if (!is_correct_hex_coordinates(hexagon, file)){
		return -1;
	}

	//checking correct radius
	if (hexagon->radius < 2){
		printf("\x1b[31mRadius too small.\x1b[0m\n");
		return -1;
	}
	
	//create an array of vertices
	unsigned int count_vertices = 6;
	Point *points_arr = malloc((count_vertices+1)*sizeof(Point));
	if (points_arr == NULL){
		printf("\x1b[31mIt is impossible to allocate memory for an array of vertices.\x1b[0m\n");
		return -1;
	}

	//draw hexagon boarder
	for (int j = hexagon->radius; j <= hexagon->radius + hexagon->line_width; j++){
		get_hexpoints(hexagon->center.x, hexagon->center.y, j, arr, points_arr);
		for (int i = 0; i < count_vertices; i++){
			draw_line(points_arr[i].x, points_arr[i].y, points_arr[i+1].x, points_arr[i+1].y, arr, &hexagon->line_color);
		}
	}

	//free array of vertices
	free(points_arr);

	//fill hexagon
	if (hexagon->flags[2]){
		hexagon_flood_fill(hexagon->center.x, hexagon->center.y, arr, &hexagon->filling_color, &hexagon->line_color);
		hexagon_flood_fill(hexagon->center.x + (hexagon->radius-2), hexagon->center.y, arr, &hexagon->filling_color, &hexagon->line_color);
		hexagon_flood_fill(hexagon->center.x - (hexagon->radius-2), hexagon->center.y, arr, &hexagon->filling_color, &hexagon->line_color);
		hexagon_flood_fill(hexagon->center.x, hexagon->center.y + (hexagon->radius/2), arr, &hexagon->filling_color, &hexagon->line_color);
		hexagon_flood_fill(hexagon->center.x, hexagon->center.y - (hexagon->radius/2), arr, &hexagon->filling_color, &hexagon->line_color);
	}

	return 0;
}

