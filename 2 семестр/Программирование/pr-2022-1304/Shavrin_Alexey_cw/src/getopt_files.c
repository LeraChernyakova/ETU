#include <stdio.h>
#include <string.h>
#include "getopt.h"
#include "structs.h"


int is_bmp(char *arg){
        if (strstr(arg, ".bmp") != NULL){
                return 1;
        }

        return 0;
}


int case_input_file(Configs *config, char *optarg){
        if (is_bmp(optarg)){
                strcpy(config->input_file, optarg);
                return 0;
        } else{
                printf("%s - \x1b[31mInput file is not BMP!\x1b[0m\n", optarg);
                return -1;
        }
}


int case_output_file(Configs *config, char *optarg){
        if (is_bmp(optarg)){
                strcpy(config->output_file, optarg);
                return 0;
        } else{
                printf("%s - \x1b[31mOutput file is not BMP!\x1b[0m\n", optarg);
                return -1;
        }
}


int search_input_file(int argc, char *argv[], int *optind, Configs *config){
        argc -= (*optind);
        argv += (*optind);

	//checking for the presence of the name of the multable file
	if (!strstr(config->input_file, ".bmp")){
        	for(int i=0; i<argc; i++){
			if (is_bmp(argv[i])){
				strcpy(config->input_file, argv[i]);
        	                return 1;
			}
		}
	} else{
		return 1;
	}

	return 0;
}


void no_input_file(){
	printf("\x1b[31mInput file name wasn't given!\x1b[0m\n");
}

