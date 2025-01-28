#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "draw_common_func.h"


void draw_koch_curve(double x0, double y0, double x1, double y1, int n, double angle, Rgb **arr, Rgb *color){
	if (n == 0){
		//draw line
		draw_line((int)x0, (int)y0, (int)x1, (int)y1, arr, color);
		return;
	}
	//delta
	double delta_x = (x1 - x0)/3;
	double delta_y = (y1 - y0)/3;

	//new coordinates
	double new_x0 = x0 + delta_x;
	double new_y0 = y0 + delta_y;
	double new_x1 = x1 - delta_x;
	double new_y1 = y1 - delta_y;
	
	//middle
	double mid_x = (delta_x/2) - (delta_y*sin(angle)) + new_x0;
	double mid_y = (delta_y/2) + (delta_x*sin(angle)) + new_y0;
	
	//recursion
	draw_koch_curve(x0, y0, new_x0, new_y0, n-1, angle, arr, color);
	draw_koch_curve(new_x0, new_y0, mid_x, mid_y, n-1, angle, arr, color);
	draw_koch_curve(mid_x, mid_y, new_x1, new_y1, n-1, angle, arr, color);
	draw_koch_curve(new_x1, new_y1, x1, y1, n-1, angle, arr, color);

}


void draw_frame_koch(Frame *frame, Rgb **arr, File *file){
	int n = 3;

	//getting the best parameters
	double step_x = 3*(2*frame->width/sqrt(3));
	double step_y = 3*(2*frame->width/sqrt(3));
       	int count_x = ceil(file->W/step_x);	
       	int count_y = ceil(file->H/step_y);

	while (file->W-1 < count_x*step_x){
		step_x -= 0.0001;
	}
	while (file->H-1 < count_y*step_y){
		step_y -= 0.0001;
	}

	double angle = M_PI/3;
	
	//draw frame Koch
	for (int i = 0; i < count_x; i++){
		//bottom border
		draw_koch_curve(i*step_x, 0, (1+i)*step_x, 0, n, angle, arr, &frame->edge_color);
		//upper border
		draw_koch_curve(i*step_x, file->H-1, (1+i)*step_x, file->H-1, n, -angle, arr, &frame->edge_color);
	}
	for (int j = 0; j < count_y; j++){
		//left border
		draw_koch_curve(0, j*step_y, 0, (1+j)*step_y, n, -angle, arr, &frame->edge_color);
		//right border
		draw_koch_curve(file->W-1, j*step_y, file->W-1, (1+j)*step_y, n, angle, arr, &frame->edge_color);
	}
}
