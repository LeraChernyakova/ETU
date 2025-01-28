#include <stdio.h>
#include <stdlib.h>
#include "getopt.h"
#include "structs.h"
#include "draw_frame.h"
#include "draw_common_func.h"
#include "draw_frame_serp.h"
#include "draw_frame_koch.h"
#include "draw_frame_minc.h"


void draw_bg_frame(Frame *frame, Rgb **arr, File *file){
	//definiting borders of the frame
	int up = file->H-1 - frame->width;
	int down = 0 + frame->width;
	int left = 0 + frame->width;
	int right = file->W-1 - frame->width;

	//draw background frame
	for (int i = 0; i < file->H; i++){
		for (int j = 0; j < file->W; j++){
			if (i < down || i > up){
				set_pixel(&arr[i][j], &frame->bg_color);
			}
			if (j < left || j > right){
				set_pixel(&arr[i][j], &frame->bg_color);
			}
		}
	}
}


int DrawFrame(Frame *frame, Rgb **arr, File *file){
	//validation of border width value
	if (frame->width > file->W/2 || frame->width > file->H/2 || frame->width <= 0){
		printf("\x1b[31mUnacceptably frame width value\x1b[0m\n");
		return -1;
	}

	//draw background frame
	draw_bg_frame(frame, arr, file);

	//draw pattern
	switch (frame->type){
		case 0:
			draw_frame_serp(frame, arr, file);
			break;

		case 1:
			//checking minimum border
			if (frame->width < 10){
				printf("\x1b[31mPattern number 1 requires a minimum border width of 10px\x1b[0m\n");
				return -1;
			}
			draw_frame_koch(frame, arr, file);
			break;

		case 2:
			//checking minimum border
			if (frame->width < 17){
				printf("\x1b[31mPattern number 2 requires a minimum border width of 17px\x1b[0m\n");
				return -1;
			}
			draw_frame_minc(frame, arr, file);
			break;

		default:
			printf("\x1b[31mIntroduced non-existen frame type\x1b[0m\n");
			return -1;
	}

	return 0;
}
