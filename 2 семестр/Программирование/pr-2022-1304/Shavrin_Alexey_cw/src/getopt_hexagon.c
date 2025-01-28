#include <stdio.h>
#include <stdlib.h>
#include "getopt.h"
#include "structs.h"


int case_hexstart(int argc, char *argv[], int *optind, Configs *config, Hexagon *hexagon){
        //flag passing check
        if (config->draw_hexagon){
                int args[2];    //temporary array of arguments
                int count = read_args(argc, argv, optind, 2, args);     //number of arguments read

                //error checking
                if (count == -1){
                        printf("\x1b[31mFlag {--hexstart} takes arguments of type int\x1b[0m\n");
                        return -1;
                }

                //checking if all arguments are passed
                if (count == 2){
                                hexagon->start.x = args[0];
                                hexagon->start.y = args[1];
                        return 0;
                } else{
                        printf("\x1b[31mFlag {--hexstart} taken 2 argument, but was given less argument\x1b[0m\n");
                        return -1;
                }
        } else{
                printf("\x1b[31mCopy flag {-x}/{--hexagon} not specified!\x1b[0m\n");
                return -1;
        }
}


int case_hexend(int argc, char *argv[], int *optind, Configs *config, Hexagon *hexagon){
        //flag passing check
        if (config->draw_hexagon){
                int args[2];    //temporary array of arguments
                int count = read_args(argc, argv, optind, 2, args);     //number of arguments read

                //error checking
                if (count == -1){
                        printf("\x1b[31mFlag {--hexend} takes arguments of type int\x1b[0m\n");
                        return -1;
                }

                //checking if all arguments are passed
                if (count == 2){
                                hexagon->end.x = args[0];
                                hexagon->end.y = args[1];
                        return 0;
                } else{
                        printf("\x1b[31mFlag {--hexend} taken 2 argument, but was given less argument\x1b[0m\n");
                        return -1;
                }
        } else{
                printf("\x1b[31mCopy flag {-x}/{--hexagon} not specified!\x1b[0m\n");
                return -1;
        }
}


int case_hexcenter(int argc, char *argv[], int *optind, Configs *config, Hexagon *hexagon){
	//flag passing check
	if (config->draw_hexagon){
		int args[2];	//temporary array of arguments
		int count = read_args(argc, argv, optind, 2, args);	//number of arguments read
		
		//error checking
		if (count == -1){
			printf("\x1b[31mFlag {--center} takes arguments of type int\x1b[0m\n");
			return -1;
		}
		
		//checking if all arguments are passed
		if (count == 2){
			hexagon->center.x = args[0];
			hexagon->center.y = args[1];
			return 0;
		} else{
			printf("\x1b[31mFlag {--center} taken 2 argument, but was given less argument\x1b[0m\n");
			return -1;
		}
	} else{
		printf("\x1b[31mHexagon flag {-x}/{--hexagon} not specified!\x1b[0m\n");
		return -1;
	}
}


int case_hexradius(int argc, char *argv[], char *optarg, Configs *config, Hexagon *hexagon){
	//flag passing check
	if (config->draw_hexagon){
		
		//error checking
		if (!is_number(optarg)){
			printf("\x1b[31mFlag {--radius} takes argument of type int\x1b[0m\n");
			return -1;
		}
		
		hexagon->radius = atoi(optarg);
		return 0;
	} else{
		printf("\x1b[31mHexagon flag {-x}/{--hexagon} not specified!\x1b[0m\n");
		return -1;
	}
}


int case_hexline_width(int argc, char *argv[], char *optarg, Configs *config, Hexagon *hexagon){
        //flag passing check
        if (config->draw_hexagon){

                //error checking
                if (!is_number(optarg)){
                        printf("\x1b[31mFlag {--linewidth} takes argument of type int\x1b[0m\n");
                        return -1;
                }

                hexagon->line_width = atoi(optarg);
                return 0;
        } else{
                printf("\x1b[31mHexagon flag {-x}/{--hexagon} not specified!\x1b[0m\n");
                return -1;
        }
}


int case_hexline_color(int argc, char *argv[], int *optind, Configs *config, Hexagon *hexagon){
        //flag passing check
        if (config->draw_hexagon){
                int args[3];    //temporary array of arguments
                int count = read_args(argc, argv, optind, 3, args);     //number of arguments read

                //error checking
                if (count == -1){
                        printf("\x1b[31mFlag {--linergb} takes arguments of type int\x1b[0m\n");
                        return -1;
                }

                if (!is_rgb_numbers(args)){
                        return -1;
                }

                //checking if all arguments are passed
                if (count == 3){
                        hexagon->line_color = (Rgb){args[2], args[1], args[0]};
                        return 0;
                } else{
                        printf("\x1b[31mFlag {--linergb} taken 3 argument, but was given less argument\x1b[0m\n");
                        return -1;
                }
        } else{
                printf("\x1b[31mHexagon flag {-x}/{--hexagon} not specified!\x1b[0m\n");
                return -1;
        }
}


int case_hexfilling(int argc, char *argv[], int *optind, Configs *config, Hexagon *hexagon){
	//flag passing check
	if (config->draw_hexagon){
		int args[3];	//temporary array of arguments
		int count = read_args(argc, argv, optind, 3, args);	//number of arguments read

		//error checking
		if (count == -1){
			printf("\x1b[31mFlag {-f}/{--fill} takes arguments of type int\x1b[0m\n");
			return -1;
		}

		if (!is_rgb_numbers(args)){
			return -1;
		} 
		
		//checking if all arguments are passed
		if (count == 3){
			hexagon->filling_color = (Rgb){args[2], args[1], args[0]};
			return 0;
		} else{
			printf("\x1b[31mFlag {-f}/{--fill} taken 3 argument, but was given less argument\x1b[0m\n");
			return -1;
		}
	} else{
		printf("\x1b[31mHexagon flag {-x}/{--hexagon} not specified!\x1b[0m\n");
		return -1;
	}
}
