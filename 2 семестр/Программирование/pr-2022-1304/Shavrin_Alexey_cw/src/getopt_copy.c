#include <stdio.h>
#include <getopt.h>
#include "getopt.h"
#include "structs.h"


int case_start_copy(int argc, char *argv[], int *optind, Configs *config, Area *area){
        //flag passing check
        if (config->copy_area){
                int args[2];    //temporary array of arguments
                int count = read_args(argc, argv, optind, 2, args);     //number of arguments read

                //error checking
                if (count == -1){
                        printf("\x1b[31mFlag {--start} takes arguments of type int\x1b[0m\n");
                        return -1;
                }

                //checking if all arguments are passed
                if (count == 2){
                                area->start.x = args[0];
                                area->start.y = args[1];
                        return 0;
                } else{
                        printf("\x1b[31mFlag {--start} taken 2 argument, but was given less argument\x1b[0m\n");
                        return -1;
                }
        } else{
                printf("\x1b[31mCopy flag {-c}/{--copy} not specified!\x1b[0m\n");
                return -1;
        }
}


int case_end_copy(int argc, char *argv[], int *optind, Configs *config, Area *area){
	//flag passing check
	if (config->copy_area){
		int args[2];	//temporary array of arguments
		int count = read_args(argc, argv, optind, 2, args);	//number of arguments read

		//error checking
		if (count == -1){
			printf("\x1b[31mFlag {--end} takes arguments of type int\x1b[0m\n");
			return -1;
		}

		//checking if all arguments are passed
		if (count == 2){
				area->end.x = args[0];
				area->end.y = args[1];
			return 0;
		} else{
			printf("\x1b[31mFlag {--end} taken 2 argument, but was given less argument\x1b[0m\n");
			return -1;
		}
	} else{
		printf("\x1b[31mCopy flag {-c}/{--copy} not specified!\x1b[0m\n");
		return -1;
	}
}


int case_insert(int argc, char *argv[], int *optind, Configs *config, Area *area){
	//flag passing check
	if (config->copy_area){
		int args[2];	//temporary array of arguments
		int count = read_args(argc, argv, optind, 2, args);	//number of arguments read

		//error checking
		if (count == -1){
			printf("\x1b[31mFlag {--insert} takes arguments of type int\x1b[0m\n");
			return -1;
		}

		//checking if all arguments are passed
		if (count == 2){
				area->insert.x = args[0];
				area->insert.y = args[1];
			return 0;
		} else{
			printf("\x1b[31mFlag {--insert} taken 2 argument, but was given less argument\x1b[0m\n");
			return -1;
		}
	} else{
		printf("\x1b[31mCopy flag {-c}/{--copy} not specified!\x1b[0m\n");
		return -1;
	}
}

