#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "draw_common_func.h"
#include <math.h>


void draw_minkovsky_curve(int x0, int y0, int x1, int y1, int n, Rgb **arr, Rgb *color){
	if (n == 0){
		//draw line
		draw_line(x0, y0, x1, y1, arr, color);
		return;
	}

	//array of line points
	int x[9];
	int y[9];

	x[0] = x0;
	y[0] = y0;
	x[8] = x1;
	y[8] = y1;

	int delta;
	
	//slope detection
	if (y0 == y1){
		delta = (x1 - x0)/4;

		//getting new points
		x[1] = x[2] = x[0] + delta;
		x[3] = x[4] = x[5] = x[2] + delta;
		x[6] = x[7] = x[3] + delta;

		y[1] = y[4] = y[7] = y[0];
		y[2] = y[3] = y[0] - delta;
		y[5] = y[6] = y[0] + delta;
		
	} else{ 
		delta = (y1 - y0)/4;
		
		//getting new points
		y[1] = y[2] = y[0] + delta;
		y[3] = y[4] = y[5] = y[2] + delta;
		y[6] = y[7] = y[3] + delta;

		x[1] = x[4] = x[7] = x[0];
		x[2] = x[3] = x[0] - delta;
		x[5] = x[6] = x[0] + delta;
	}

	//recursive calls of drawing a curve
	for (int i = 0; i < 8; i++) { 
		draw_minkovsky_curve(x[i], y[i], x[i+1], y[i+1], n-1, arr, color);
	}
}


void draw_frame_minc(Frame *frame, Rgb **arr, File *file){
	int n = 2;

	//getting the best parameters
	double step_x = frame->width;
	double step_y = frame->width;
       	int count_x = ceil(file->W/step_x);	
       	int count_y = ceil(file->H/step_y);

	while (file->W-1 < count_x*step_x){
		step_x -= 0.000001;
	}
	while (file->H-1 < count_y*step_y){
		step_y -= 0.000001;
	}
	
	//draw frame	
	for (int i = 0; i < count_x; i++){
		//bottom border
		draw_minkovsky_curve((0+i)*step_x, step_y/2, (1+i)*step_x, step_y/2, n, arr, &frame->edge_color);
		//upper border
		draw_minkovsky_curve((0+i)*step_x, file->H - step_y/2, (1+i)*step_x, file->H - step_y/2, n, arr, &frame->edge_color);
	}

	for (int i = 0; i < count_y; i++){
		//right border
		draw_minkovsky_curve(file->W - step_x/2, (0+i)*step_y, file->W - step_x/2, (1+i)*step_y, n, arr, &frame->edge_color);
		//left border
		draw_minkovsky_curve(step_x/2, (0+i)*step_y, step_x/2, (1+i)*step_y, n, arr, &frame->edge_color);
	}
}
