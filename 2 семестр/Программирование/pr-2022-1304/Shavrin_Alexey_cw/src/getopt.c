#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void PrintHelp(){
	//hint
	printf("\n\t\x1b[32mGETOPT HINT\x1b[0m\n\n");

	//general	
	printf("\x1b[33m__________________________________________________________________________GENERAL______________________________________________________________________________________________\x1b[0m\n");
	printf("\t\x1b[33mGeneral\x1b[0m\n");
	printf("\x1b[35m-h -? --help\x1b[0m <-- help\n");
	printf("\x1b[35m--bmpversion\x1b[0m <-- supported bmp file versions\n");
	printf("\x1b[35m--bmpinfo\x1b[0m <-- bmp file information\n");

	printf("\x1b[35m-i\x1b[36m <filename.bmp> \x1b[35m--inputfile\x1b[36m <filename.bmp>\x1b[0m <-- input BMP file (file to be changed)\n");
	printf("\x1b[35m-o\x1b[36m <filename.bmp> \x1b[35m--outputfile\x1b[36m <filename.bmp>\x1b[0m <-- output BMP file (file were changes are saved)\n\n");
	
	//hexagon
	printf("\x1b[33m__________________________________________________________________________HEXAGON______________________________________________________________________________________________\x1b[0m\n");
	printf("\t\x1b[33mHexagon\x1b[0m\n");
	printf("\x1b[35m-x --hexagon\x1b[0m <-- draw regular hexagon flag\n");
	printf("\t\x1b[35m--center\x1b[36m <x> <y>\x1b[0m <-- coordinates (type int) of the center of the hexagon (the origin is in the lower left corner)\n");
	printf("\t\x1b[35m--radius\x1b[36m <radius>\x1b[0m <-- hexagon radius (type int)\n");
	
	printf("\n\x1b[32mInstead of the coordinates of the center and radius, you can set the coordinates of the left upper and right down corner of the square in which it is inscribed\x1b[0m\n");
	printf("\t\x1b[35m--hexstart\x1b[36m <x> <y>\x1b[0m <-- coordinates (type int) of the upper left corner of the copy area (x, y)(the origin is in the lower left corner)\n");
        printf("\t\x1b[35m--hexend\x1b[36m <x> <y>\x1b[0m <-- coordinates (type int) of the lower right corner of the copy area (x, y)(the origin is in the lower left corner)\n\n");

	printf("\t\x1b[35m--linewidth\x1b[36m <width>\x1b[0m <-- boarder width (default: 1px)\n");
	printf("\t\x1b[35m--linergb\x1b[36m <red> <green> <blue>\x1b[0m <-- boarder color (default: (0, 0, 0)) (each color component ranging from 0 to 255)\n");
	printf("\t\x1b[35m-f\x1b[36m <red> <green> <blue> \x1b[35m--fill\x1b[36m <red> <green> <blue>\x1b[0m <-- hexagon fill color (each color component ranging from 0 to 255)\n\n");

	//copy area
	printf("\x1b[33m__________________________________________________________________________COPY_AREA____________________________________________________________________________________________\x1b[0m\n");
	printf("\t\x1b[33mCopy area\x1b[0m\n");
	printf("\x1b[35m-c --copy\x1b[0m <-- copy area flag\n");
	printf("\t\x1b[35m--start\x1b[36m <x> <y>\x1b[0m <-- coordinates (type int) of the upper left corner of the copy area (x, y)(the origin is in the lower left corner)\n");
	printf("\t\x1b[35m--end\x1b[36m <x> <y>\x1b[0m <-- coordinates (type int) of the lower right corner of the copy area (x, y)(the origin is in the lower left corner)\n");
	printf("\t\x1b[35m--insert\x1b[36m <x> <y>\x1b[0m <-- coordinates (type int) of thr upper left corner of the paste area (x, y)\n\n");

 	//switch color
	printf("\x1b[33m__________________________________________________________________________SWITCH_COLOR_________________________________________________________________________________________\x1b[0m\n");
	printf("\t\x1b[33mSwitch color\x1b[0m\n");
	printf("\x1b[35m-s --switchcolor\x1b[0m <-- switch color flag\n");
	printf("\t\x1b[35m--old\x1b[36m <red> <green> <blue>\x1b[0m <-- color to be change (each color component ranging from 0 to 255)\n");
	printf("\t\x1b[35m--new\x1b[36m <red> <green> <blue>\x1b[0m <-- color to be applied (each color component ranging from 0 to 255)\n\n");
	
	//frame
	printf("\x1b[33m__________________________________________________________________________FRAME________________________________________________________________________________________________\x1b[0m\n");
	printf("\t\x1b[33mFrame\x1b[0m\n");
	printf("\x1b[35m-e --edge\x1b[0m <-- frame flag\n");
	printf("\t\x1b[35m--type\x1b[36m <pattern>\x1b[0m> <-- frame pattern {0, 1, 2} (default: 0)\n");
	printf("\t\x1b[35m--width\x1b[36m <width>\x1b[0m> <-- frame width (default: 20px)\n");
	printf("\t\x1b[35m--edgergb\x1b[36m <red> <green> <blue>\x1b[0m <-- frame color (default: (255, 255, 255)) (each color component ranging from 0 to 255)\n");
	printf("\t\x1b[35m--bgrgb\x1b[36m <red> <green> <blue>\x1b[0m <-- background frame color (default: (0, 0, 0)) (each color component ranging from 0 to 255)\n\n");
}


int is_number(char *arg){
	if (atoi(arg) || (!atoi(arg) && isdigit(arg[0]))){
		return 1;
	}
	return 0;
}


int is_rgb_numbers(int args[]){
	//iterate over all rgb arguments
	for (int i = 0; i < 3; i++){

		//conformity check
		if (args[i]<0 || args[i]>255){
			printf("\x1b[31mArgumentes <red> <green> <blue> must be in the range from 0 to 255\x1b[0m\n");
			return 0;	
		}
	}
	return 1;
}


int read_args(int argc, char *argv[], int *optind, int count, int args[]){
        (*optind)--;
        int i = 0;

        //iterate over all arguments passed after the flag
        for (;*optind < argc && *argv[*optind]!='-' && i < count; (*optind)++){

                //type matching check
                if (is_number(argv[*optind])){
                        args[i++] = atoi(argv[*optind]);
                } else{
                        return -1;
                }
        }

        return i;
}

