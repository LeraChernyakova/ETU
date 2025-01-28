#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "draw_common_func.h"


void draw_serp(double x0, double y0, double x1, double y1, int n, Rgb **arr, Rgb *color){
	if (n > 0){
		//new coordinates
		double new_x0 = 2*x0/3 + x1/3;
		double new_y0 = 2*y0/3 + y1/3;
		double new_x1 = x0/3 + 2*x1/3;
		double new_y1 = y0/3 + 2*y1/3;

		//draw rectangle
		draw_rectangle((int)new_x0, (int)new_y0, (int)new_x1, (int)new_y1, arr, color);

		//recursion
		draw_serp(x0, y0, new_x0, new_y0, n-1, arr, color);
		draw_serp(new_x0, y0, new_x1, new_y0, n-1, arr, color);
		draw_serp(new_x1, y0, x1, new_y0, n-1, arr, color);
		draw_serp(x0, new_y0, new_x0, new_y1, n-1, arr, color);
		draw_serp(new_x1, new_y0, x1, new_y1, n-1, arr, color);
		draw_serp(x0, new_y1, new_x0, y1, n-1, arr, color);
		draw_serp(new_x0, new_y1, new_x1, y1, n-1, arr, color);
		draw_serp(new_x1, new_y1, x1, y1, n-1, arr, color);
	}
}


void draw_frame_serp(Frame *frame, Rgb **arr, File *file){
	int n = 4;

	//getting the best parameters
	double step_x = frame->width;
	double step_y = frame->width;
       	int count_x = ceil(file->W/step_x);	
       	int count_y = ceil(file->H/step_y);

	while (file->W-1 < count_x*step_x){
		step_x -= 0.0001;
	}
	while (file->H-1 < count_y*step_y){
		step_y -= 0.0001;
	}
	
	//draw frame
	for (int i = 0; i < file->W/frame->width; i++){
		//bottom border
		draw_serp(0+i*step_x, step_y, (i+1)*step_x, 0, n, arr, &frame->edge_color);
		//upper border
		draw_serp(file->W - (i+1)*step_x, file->H, file->W - i*step_x, file->H - step_y, n, arr, &frame->edge_color);
	}
	for (int i = 0; i < file->H/frame->width; i++){
		//left border
		draw_serp(0, file->H - i*step_y, step_x, file->H - (i+1)*step_y, n, arr, &frame->edge_color);
		//right border
		draw_serp(file->W - step_x, (i+1)*step_y, file->W, i*step_y, n, arr, &frame->edge_color);
	}
}

