#include <stdio.h>
#include <stdlib.h>
#include "getopt.h"
#include "structs.h"


int case_edge_type(int argc, char *argv[], char *optarg, Configs *config, Frame *frame){
	//flag passing check
	if (config->draw_frame){
		
		//error checking
		if (!is_number(optarg)){
			printf("\x1b[31mFlag {--type} takes arguments of type int\x1b[0m\n");
			return -1;
		}

		frame->type = atoi(optarg);
		return 0;
	} else{
		printf("\x1b[31mDraw frame flag {-e}/{--edge} not specified!\x1b[0m\n");
		return -1;
	}
}


int case_edge_width(int argc, char *argv[], char *optarg, Configs *config, Frame *frame){
	//flag passing check
	if (config->draw_frame){
		
		//error checking
		if (!is_number(optarg)){
			printf("\x1b[31mFlag {--breadth} takes arguments of type int\x1b[0m\n");
			return -1;
		}

		frame->width = atoi(optarg);
		return 0;
	} else{
		printf("\x1b[31mDraw frame flag {-e}/{--edge} not specified!\x1b[0m\n");
		return -1;
	}
}


int case_edge_color(int argc, char *argv[], int *optind, Configs *config, Frame *frame){
	//flag passing check
	if (config->draw_frame){
		int args[3];	//temporary array of arguments
		int count = read_args(argc, argv, optind, 3, args);	//number of arguments read
		
		//error checking
		if (count == -1){
			printf("\x1b[31mFlag {--edgergb} takes arguments of type int\x1b[0m\n");
			return -1;
		}

		//checking if all arguments are passed
		if (count == 3){
			if (!is_rgb_numbers(args)){
				return -1;
			}

			frame->edge_color = (Rgb){args[2], args[1], args[0]};
			return 0;
		} else{
			printf("\x1b[31mFlag {--edgergb} taken 3 argument, but was given less argument\x1b[0m\n");
			return -1;
		}
	} else{
		printf("\x1b[31mDraw frame flag {-e}/{--edge} not specified!\x1b[0m\n");
		return -1;
	}
}


int case_bg_color(int argc, char *argv[], int *optind, Configs *config, Frame *frame){
	//flag passing check
	if (config->draw_frame){
		int args[3];	//temporary array of arguments
		int count = read_args(argc, argv, optind, 3, args);	//number of arguments read
		
		//error checking
		if (count == -1){
			printf("\x1b[31mFlag {--bgrgb} takes arguments of type int\x1b[0m\n");
			return -1;
		}

		//checking if all arguments are passed
		if (count == 3){
			if (!is_rgb_numbers(args)){
				return -1;
			}

			frame->bg_color = (Rgb){args[2], args[1], args[0]};
			return 0;
		} else{
			printf("\x1b[31mFlag {--bgrgb} taken 3 argument, but was given less argument\x1b[0m\n");
			return -1;
		}
	} else{
		printf("\x1b[31mDraw frame flag {-e}/{--edge} not specified!\x1b[0m\n");
		return -1;
	}
}
