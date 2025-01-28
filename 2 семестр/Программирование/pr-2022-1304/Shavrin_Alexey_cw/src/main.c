#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "structs.h"
#include "getopt.h"
#include "getopt_files.h"
#include "bmp_info.h"
#include "getopt_copy.h"
#include "getopt_hexagon.h"
#include "getopt_switch_color.h"
#include "getopt_frame.h"
#include "copy_area.h"
#include "switch_color.h"
#include "draw_hexagon.h"
#include "draw_frame.h"
#include "file_processing.h"
#define OUTPUT_FILE_NAME "out.bmp"



int main(int argc, char *argv[]){

	//start init structs
	Configs config = {0, 0, 0, 0, calloc(50, sizeof(char)), calloc(50, sizeof(char))};
	strcpy(config.output_file, OUTPUT_FILE_NAME);
	Hexagon hexagon = {{0, 0, 0, 0, 0}, {0, 0}, {0, 0}, {0, 0}, 0, 1, {0, 0, 0}};
	SwitchColor switch_color = {{0, 0}, {0, 0, 0}, {0, 0, 0}};
	Area area = {{0, 0, 0}, {0, 0}, {0, 0}, 0, 0,  {0, 0}};
	Frame frame = {0, 20, {255, 255, 255}, {0, 0, 0}};	

//__________________________________________________________GETOPT_________________________________________________________

	char *opts = "h?i:o:xf:cse";
	struct option LongOpts[]={
        	 {"help", no_argument, NULL, 'h'},
       		 {"bmpversion", no_argument, NULL, 0},
        	 {"bmpinfo", no_argument, NULL, 0},
        	 {"inputfile", required_argument, NULL, 'i'},
        	 {"outfile", required_argument, NULL, 'o'},
		 {"hexagon", no_argument, NULL, 'x'},
		 {"hexstart", required_argument, NULL, 14},
		 {"hexend", required_argument, NULL, 15},
		 {"center", required_argument, NULL, 1},
		 {"radius", required_argument, NULL, 2},
		 {"linewidth", required_argument, NULL, 3},
		 {"linergb", required_argument, NULL, 4},
        	 {"fill", required_argument, NULL, 'f'},
        	 {"copy", no_argument, NULL, 'c'},
		 {"start", required_argument, NULL, 5},
		 {"end", required_argument, NULL, 6},
		 {"insert", required_argument, NULL, 7},
        	 {"switchcolor", no_argument, NULL, 's'},
		 {"old", required_argument, NULL, 8},
		 {"new", required_argument, NULL, 9},
        	 {"edge", no_argument, NULL, 'e'},
		 {"type", required_argument, NULL, 10},
		 {"width", required_argument, NULL, 11},
		 {"edgergb", required_argument, NULL, 12},
		 {"bgrgb", required_argument, NULL, 13},
        	 { NULL, no_argument, NULL, 0}
	};

	int opt;
        int longIndex;
        opt = getopt_long(argc, argv, opts, LongOpts, &longIndex);
	
	//checking the launch of the program without flags
	if (opt == -1){
		PrintHelp();
		return 0;
	}

        while(opt!=-1){
                switch(opt){
//__________________________________________________________INPUT_FILENAME_________________________________________________________
			case 'i':
				if (case_input_file(&config, optarg) == -1){
					return -1;
				}
                                break;

//__________________________________________________________OUTPUT_FILENAME________________________________________________________
                        case 'o':
				if (case_output_file(&config, optarg) == -1){
					return -1;
				}
                                break;

//__________________________________________________________HEXAGON________________________________________________________________
                        case 'x':
				//hexagon
				config.draw_hexagon = 1;
				break;	

			case 14:
				//hexstart
				hexagon.flags[3] = 1;
				if (case_hexstart(argc, argv, &optind, &config, &hexagon) == -1){
					return -1;
				}
				break;

			case 15:
				//hexend
				hexagon.flags[4] = 1;
				if (case_hexend(argc, argv, &optind, &config, &hexagon) == -1){
					return -1;
				}
				break;

			case 1:
				//hexcenter
				hexagon.flags[0] = 1;
				if (case_hexcenter(argc, argv, &optind, &config, &hexagon) == -1){
					return -1;
				}
				break;

			case 2:
				//hexradius
				hexagon.flags[1] = 1;
				if (case_hexradius(argc, argv, optarg, &config, &hexagon) == -1){
					return -1;
				}
				break;

			case 3:
				//hexline_width
				if (case_hexline_width(argc, argv, optarg, &config, &hexagon) == -1){
					return -1;
				}
				break;

			case 4:
				//hexline_color
				if (case_hexline_color(argc, argv, &optind, &config, &hexagon) == -1){
					return -1;
				}
				break;

			case 'f':
				//hexfilling
				hexagon.flags[2] = 1;
				if (case_hexfilling(argc, argv, &optind, &config, &hexagon) == -1){
					return -1;
				}
				break;	
//__________________________________________________________COPY_AREA______________________________________________________________

			case 'c':
				//copy
				config.copy_area = 1;
				break;

			case 5:
				//start copy
				area.flags[0] = 1;
				if (case_start_copy(argc, argv, &optind, &config, &area) == -1){
					return -1;
				}
				break;

			case 6:
				//end copy
				area.flags[1] = 1;
				if (case_end_copy(argc, argv, &optind, &config, &area) == -1){
					return -1;
				}
				break;

			case 7:
				//insert copy
				area.flags[2] = 1;
				if (case_insert(argc, argv, &optind, &config, &area) == -1){
					return -1;
				}
				break;
//__________________________________________________________SWITCH_COLOR___________________________________________________________

			case 's':
				//switch color
				config.switch_color = 1;
				break;
			
			case 8:
				//old color
				switch_color.flags[0] = 1;
				if (case_old_color(argc, argv, &optind, &config, &switch_color) == -1){
					return -1;
				}
				break;

			case 9:
				//new color
				switch_color.flags[1] = 1;
				if (case_new_color(argc, argv, &optind, &config, &switch_color) == -1){
					return -1;
				}
				break;
//__________________________________________________________FRAME___________________________________________________________________

			case 'e':
				//frame
				config.draw_frame = 1;
				break;	
			
			case 10:
				//edge type
				if (case_edge_type(argc, argv, optarg, &config, &frame) == -1){
					return -1;
				}
				break;

			case 11:
				//edge width
				if (case_edge_width(argc, argv, optarg, &config, &frame) == -1){
					return -1;
				}
				break;

			case 12:
				//edge color
				if (case_edge_color(argc, argv, &optind, &config, &frame) == -1){
					return -1;
				}
				break;

			case 13:
				//background color
				if (case_bg_color(argc, argv, &optind, &config, &frame) == -1){
					return -1;
				}
				break;
//__________________________________________________________INFO____________________________________________________________________

                        case 0:
                                if (!strcmp(LongOpts[longIndex].name, "bmpversion")){
					printf("This program supports only 24 bits per pixel version of bmp file!\n");
				} else{
					config.bmp_info = 1;
				}
				break;
//__________________________________________________________HELP____________________________________________________________________
                        case 'h':
                        case '?':
			default:
                        	PrintHelp();
                                return 0;
                }
                opt = getopt_long(argc, argv, opts, LongOpts, &longIndex);
        }

	//checking multable file
	if (!search_input_file(argc, argv, &optind, &config)){
		no_input_file();
		return -1;
	}
	



//__________________________________________________________FILE_PROCESSING____________________________________________________________________
	//init file structs
	File file = {malloc(sizeof(BitmapFileHeader)), malloc(sizeof(BitmapInfoHeader)), 0, 0, NULL};
	BitmapFileHeader bmfh;
	BitmapInfoHeader bmih;

	//reading file
	if (read_input_file(&config, &file, &bmfh, &bmih) == -1){
		return -1;
	}

	//headlines recording
	file.bmfh = &bmfh;
	file.bmih = &bmih;
		
	//checking bmpinfo flag
	if (config.bmp_info){
		printFileHeader(*file.bmfh);
		printInfoHeader(*file.bmih);
		printf("\n");
		//return 0;
	}

	//checking bmp version
	if (file.bmih->bitsPerPixel != 24){
		printf("\x1b[31mThis file %hu bits per pixel\x1b[0m\n", file.bmih->bitsPerPixel);
		printf("\x1b[31mBut this program supports only 24 bits per pixel version of bmp file!\x1b[31m\n");
		return -1;
	}	
	

//__________________________________________________________TASK_COMPETITION____________________________________________________________________
	//tasks
	if (config.copy_area){
		//copy area
		if (CopyAreaFunc(file.arr, &area, &file) == -1){
			return -1;
		}
	}

	if (config.switch_color){
		//switch color
		if (SwitchColorFunc(file.arr, &switch_color, &file) == -1){
			return -1;
		}
	}

	if (config.draw_hexagon){
		//draw hexagon
		if (DrawHexagon(&hexagon, file.arr, &file) == -1){
			return -1;
		}
	}

	if (config.draw_frame){
		//draw frame
		if (DrawFrame(&frame, file.arr, &file) == -1){
			return -1;
		}
	}

//__________________________________________________________TOTAL____________________________________________________________________
	//writing the resulting file
	if (create_output_file(&config, &file) == -1){
		return -1;
	}

	return 0;
}
