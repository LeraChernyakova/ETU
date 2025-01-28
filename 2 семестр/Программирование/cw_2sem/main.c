#include "allinfo.h"

int main(int argc, char* argv[]){
    
    char *opts = "hicfrv"; 
	int opt;
	int longIndex;
	struct option longOpts[] = {
	        {"help", no_argument, 0, 'h'},
            {"info", no_argument, 0, 'i'},
	        {"copy", no_argument, 0, 'c'},
	        {"flip", no_argument, 0, 'f'},
	        {"round", no_argument, 0, 'r'},
            {"invert", no_argument, 0, 'v'},
	        { NULL, 0, NULL, 0}
	};
	opt = getopt_long(argc, argv, opts, longOpts, &longIndex);

    int correct = 0;

    if (opt == -1){
        printHelp();
        return 0;
    }

    if(!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")){
        printHelp();
        return 0;
    }
    else if(argv[1][0] == '-'){
        printf("\x1b[31mОшибка! Вы не ввели имя файла, который хотите обработать.\x1b[0m\n\n");
		printHelp();
		return 0;
	}
        
    if(!strcmp(argv[2],"--info") || !strcmp(argv[2],"-i")){
        image img;
        if (readFile(argv[1], &img)){
            printHelp();
            return 0;
        }
        printFileHeader(img.bmfh);
        printInfoHeader(img.bmih);
        return 0;
    }

	if(argv[argc-1][0] == '-'){
		printf("\x1b[31mОшибка! Вы не ввели имя файла, в который хотите записать результат работы программы.\x1b[0m\n\n");
		printHelp();
		return 0;
	}

    image img;
    if (readFile(argv[1], &img)){
        printHelp();
        return 0;
    }

    while (opt!=-1){
        switch(opt){
            case 'h':
                printHelp();
                break;
            case 'c':
                opt = copy(&img,argc,argv,opt,longIndex);
                break;
            case 'f':
                opt = flip(&img,argc,argv,opt,longIndex);
                break;
            case 'r':
                opt = roundopt(&img,argc,argv,opt,longIndex);
                break;
            case 'v':
                opt = invert(&img,argc,argv,opt,longIndex);
                break;
            default:
                correct = -1;
                break;
        }
        opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
    }
    if (correct == -1){
        printf("\x1b[31mВведите один из ключей, чтобы увидеть меню программы: -h/--help.\x1b[0m\n\n");
    }
    return 0;
}
