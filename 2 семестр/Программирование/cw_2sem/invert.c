#include "allinfo.h"

void invert_area(int x, int y, int a, int l, unsigned int W, unsigned int H, char *input_str, char* output_str, int checki){
    image img;
    if (readFile(input_str, &img)){
        printHelp();
        return;
    }
    if (x > W || y > H || x<0 || y<0){
        printf("\n\x1b[31mОшибка -v/--invert!\nВыбранные координаты левого верхнего угла прямоугольной области находятся за пределами изображения:\x1b[0m\n\n");
        if (x > W)
            printf("\tКоордината по горизонтальной оси, задающаяя левый верхний угол, <%d> больше ширины изображения.\n", x);
        if (x < 0)
            printf("\tКоордината по горизонатальной оси, задающаяя левый верхний угол, <%d> принимает отрицательное значение.\n", x);
        if (y > H)
            printf("\tКоордината по вертикальной оси, задающаяя левый верхний угол, <%d> больше высоты изображения.\n", y);
        if (y < 0)
            printf("\tКоордината по вертикальной оси, задающаяя левый верхний угол, <%d> принимает отрицательное значение.\n", y);
        printf("\tРазмеры изображения:\n");
        printf("\t\tВысота\t%u\n", H);
        printf("\t\tШирина\t%u\n\n", W);
        return;
    }
    if (x - 1 + l > W){
        printf("\n\x1b[31mОшибка -v/--invert!\nДлина выбранной прямоугольной области находится за пределами изображения.\x1b[0m\n\n");
        printf("\tРазмеры изображения:\n");
        printf("\t\tВысота\t%u\n", H);
        printf("\t\tШирина\t%u\n\n", W);
        return;
    }
    if (y - 1 - a < -1){
        printf("\n\x1b[31mОшибка -v/--invert!\nВысота выбранной прямоугольной области находится за пределами изображения.\x1b[0m\n\n");
        printf("\tРазмеры изображения:\n");
        printf("\t\tВысота\t%u\n", H);
        printf("\t\tШирина\t%u\n\n", W);
        return;
    }
    for (int i = 0; i < H; i++){
        for (int j = 0; j < W; j++){
            if (( j >= x - 1) && ( j < x + l - 1) && (i < y) && (i >= y -  a)){
                img.arr[i][j].r = 255 - (img.arr[i][j].r);
                img.arr[i][j].g = 255 - (img.arr[i][j].g);
                img.arr[i][j].b = 255 - (img.arr[i][j].b);
            }
        }
    }
    writeFile(output_str, checki, &img);
}

int invert(image *img, int argc, char **argv, int opt, int longIndex){
    char input_str[50];
	strcpy(input_str, argv[1]);
    struct option longOptcopy[] = {
        {"coordinate", required_argument, NULL, 'c'},
        {"length", required_argument, NULL, 'l'},
        {"altitude", required_argument, NULL, 'a'},
        {"info", required_argument, NULL, 'i'},
        {"help", required_argument, NULL, 'h'},
        { NULL, 0, NULL, 0}
    };
    char *optscopy = "c:l:a:hi";
    char *output_str = argv[argc - 1];
    int x1 = 0, y1 = 0, l = 0, a = 0;
    int correct = 0, checki = 0;
    opt = getopt_long(argc, argv, optscopy, longOptcopy, &longIndex);
    while(opt != -1){
        switch(opt){
            case 'c':
                x1 = atoi(argv[optind-1]);
                y1 = atoi(argv[optind]);
                correct++;
                break;
            case 'l':
                l = atoi(argv[optind-1]);
                correct++;
                break;
            case 'a':
                a = atoi(argv[optind-1]);
                correct++;
                break;
            case 'i':
                checki = 1;
                break;
            case 'h':
                printHelp();
                break;
            default:
                correct = -1;
                break;
        }
        opt = getopt_long(argc,argv,optscopy,longOptcopy,&longIndex);
    }
    if (correct == 3){
        invert_area(x1, y1, a, l, (int)img->bmih.width, (int)img->bmih.height, input_str, output_str, checki);
    }
    else if(correct == -1){
        printf("\x1b[31mВведите один из ключей, чтобы увидеть меню программы: -h/--help.\x1b[0m\n\n");
        exit(0);
    }
    else{
        printf ("\n\x1b[31mОшибка -c/--copy!\nВведено слишком мало аргументов для работы функции.\x1b[0m\n");
        printf("\x1b[31mВведите один из ключей, чтобы увидеть меню программы: -h/--help.\x1b[0m\n\n");
        exit(0);
    }
    return opt;
}