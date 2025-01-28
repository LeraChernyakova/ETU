#include <stdio.h>
#include "getopt.h"
#include "structs.h"


int case_old_color(int argc, char *argv[], int *optind, Configs *config, SwitchColor *switch_color){
	//flag passing check
	if (config->switch_color){
		int args[3];	//temporary array of arguments
		int count = read_args(argc, argv, optind, 3, args);	//number of arguments read

		//error checking
		if (count == -1){
			printf("\x1b[31mFlag {--old} takes arguments of type int\x1b[0m\n");
			return -1;
		}

		//checking if all arguments are passed
		if (count == 3){

			if (!is_rgb_numbers(args)){
				return -1;
			}

			switch_color->old_color = (Rgb){args[2], args[1], args[0]};
			return 0;
		} else{
			printf("\x1b[31mFlag {--old} taken 3 argument, but was given less argument\x1b[0m\n");
			return -1;
		}
	} else{
		printf("\x1b[31mSwitch color flag {-s}/{--switchcolor} not specified!\x1b[0m\n");
		return -1;
	}
}


int case_new_color(int argc, char *argv[], int *optind, Configs *config, SwitchColor *switch_color){
	//flag passing check
	if (config->switch_color){
		int args[3];	//temporary array of arguments
		int count = read_args(argc, argv, optind, 3, args);	//number of arguments read

		//error checking
		if (count == -1){
			printf("\x1b[31mFlag {--new} takes arguments of type int\x1b[0m\n");
			return -1;
		}

		//checking if all arguments are passed
		if (count == 3){

			if (!is_rgb_numbers(args)){
				return -1;
			}

			switch_color->new_color = (Rgb){args[2], args[1], args[0]};
			return 0;
		} else{
			printf("\x1b[31mFlag {--new} taken 3 argument, but was given less argument\x1b[0m\n");
			return -1;
		}
	} else{
		printf("\x1b[31mSwitch color flag {-s}/{--switchcolor} not specified!\x1b[0m\n");
		return -1;
	}
}
