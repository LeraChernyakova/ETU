#include <stdio.h>
#include "structs.h"
#include "draw_common_func.h"
#include "getopt.h"


int SwitchColorFunc(Rgb **arr, SwitchColor *switch_color, File *file){
	int y = 400;
	int x = 50;
	printf("r = %d g = %d b = %d\n", arr[y][x].r, arr[y][x].g, arr[y][x].b);
	//printf("r = %d g = %d b = %d\n", arr[y+600][x].r, arr[y+600][x].g, arr[y+600][x].b);
	//printf("r = %d g = %d b = %d\n", arr[510][720].r, arr[510][720].g, arr[510][720].b);

	//checking if all flags are passed
	if (!switch_color->flags[0] || !switch_color->flags[1]){
		printf("\x1b[31mNot all necessary flags for switch color were passed\x1b[0m\n");
		return -1;
	}
		
	for(int i=0; i<file->H; i++){
		for(int j=0; j<file->W; j++){
			if (is_check_color(&arr[i][j], &switch_color->old_color)){
				set_pixel(&arr[i][j], &switch_color->new_color);
			}
		}
	}

	return 0;
}
