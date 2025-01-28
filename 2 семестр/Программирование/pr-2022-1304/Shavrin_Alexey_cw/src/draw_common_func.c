#include <stdio.h>
#include <stdlib.h>
#include "structs.h"


void set_pixel(Rgb *pixel, Rgb *new){
	pixel->b = new->b;
	pixel->g = new->g;
	pixel->r = new->r;
}


int is_check_color(Rgb *current, Rgb *new){
	if (current->b == new->b && current->g == new->g && current->r == new->r){
		return 1;
	}
	return 0;
}


void draw_rectangle(int x0, int y0, int x1, int y1, Rgb **arr, Rgb *color){
	for (int i = y0; i > y1; i--){
		for (int j = x0; j < x1; j++){
			set_pixel(&arr[i][j], color);
		}
	}
}


void draw_line(int x0, int y0, int x1, int y1, Rgb **arr, Rgb *color){
	int delta_x = x1 - x0;
	int delta_y = y1 - y0;
	int slope;

	//checking which coordinate to change premanently
	if (abs(delta_y) > abs(delta_x)){
		slope = 1;
	} else{
		slope = -1;
	}

	int dir_y, dir_x;

	//choice to direction of change y
	if (delta_y > 0){
		dir_y = 1;
	} else{
		dir_y = -1;
	}

	//choice to direction of change x
	if (delta_x > 0){
		dir_x = 1;
	} else{
		dir_x = -1;
	}

	int error = 0;
	int x = x0;
	int y = y0;
     	set_pixel(&arr[y][x], color);

	if (slope == -1){
		do{
			error += delta_y * dir_y;
     			set_pixel(&arr[y][x+dir_x], color);
			if (error > 0){
				error -= delta_x * dir_x;
				y += dir_y;
			}
			x += dir_x;
     			set_pixel(&arr[y][x], color);
		} while (x != x1 || y != y1);
	} else{
		do{
			error += delta_x * dir_x;
     			set_pixel(&arr[y+dir_y][x], color);
			if (error > 0){
				error -= delta_y * dir_y;
				x += dir_x;
			}
			y += dir_y;
     			set_pixel(&arr[y][x], color);
		} while (x != x1 || y != y1);
	}
}
