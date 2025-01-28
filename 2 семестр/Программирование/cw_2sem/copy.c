#include "allinfo.h"

void copy_area(int x1, int y1, int x2, int y2, int x3, int y3, unsigned int W, unsigned int H, char *input_str, char* output_str, int checki){
    image img;
    if (readFile(input_str, &img)){
        printHelp();
        return;
    }
    if (x1 > W || y1 > H || x1<0 || y1<0){
        printf("\n\x1b[31mОшибка -c/--copy!\nВыбранные координаты левого верхнего угла области-источника находятся за пределами изображения:\x1b[0m\n\n");
        if (x1 > W)
            printf("\tКоордината по горизонтальной оси, задающаяя левый верхний угол, <%d> больше ширины изображения.\n", x1);
        if (x1 < 0)
            printf("\tКоордината по горизонатальной оси, задающаяя левый верхний угол, <%d> принимает отрицательное значение.\n", x1);
        if (y1 > H)
            printf("\tКоордината по вертикальной оси, задающаяя левый верхний угол, <%d> больше высоты изображения.\n", y1);
        if (y1 < 0)
            printf("\tКоордината по вертикальной оси, задающаяя левый верхний угол, <%d> принимает отрицательное значение.\n", y1);
        printf("\tРазмеры изображения:\n");
        printf("\t\tВысота\t%u\n", H);
        printf("\t\tШирина\t%u\n\n", W);
        return;
    }
    if (x2 > W || y2 > H || x2 < 0 || y2 < 0){
        printf("\n\x1b[31mОшибка -c/--copy!\nВыбранные координаты правого нижнего угла области-источника находятся за пределами изображения:\x1b[0m\n\n");
        if (x2 > W)
            printf("\tКоордината по горизонтальной оси, задающая правый нижний угол, <%d> больше ширины изображения.\n", x2);
        if (x2 < 0)
            printf("\tКоордината по горизонатальной оси, задающая правый нижний угол, <%d> принимает отрицательное значение.\n", x2);
        if (y2 > H)
            printf("\tКоордината по вертикальной оси, задающая правый нижний угол, <%d> больше высоты изображения.\n", y2);
        if (y2 < 0)
            printf("\tКоордината по вертикальной оси, задающая правый нижний угол, <%d> принимает отрицательное значение.\n", y2);
        printf("\tРазмеры изображения:\n");
        printf("\t\tВысота\t%u\n", H);
        printf("\t\tШирина\t%u\n\n", W);
        return;
    }
    if (x2 < x1){
        printf("\n\x1b[31mОшибка -c/--copy!\nКоордината х = %d правого нижнего угла должна быть больше координаты х  = %d левого верхнего угла.\x1b[0m\n\n", x2, x1);
        return;
    }
    if (y2 > y1){
        printf("\n\x1b[31mОшибка -c/--copy!\nКоордината y = %d правого нижнего угла должна быть меньше координаты y = %d левого верхнего угла.\x1b[0m\n\n", y2, y1);
        return;
    }
    if (x3 > W || y3 > H || x3 < 0 || y3 < 0){
        printf("\n\x1b[31mОшибка -c/--copy!\nВыбранные координаты левого верхнего угла области-назначения находятся за пределами изображения:\x1b[0m\n\n");
        if (x3 > W)
            printf("\tКоордината по горизонтальной оси, задающая левый верхний угол, <%d> больше ширины изображения.\n", x3);
        if (x3 < 0)
            printf("\tКоордината по горизонатальной оси, задающая левый верхний угол, <%d> принимает отрицательное значение.\n", x3);
        if (y3 > H)
            printf("\tКоордината по вертикальной оси, задающая левый верхний угол, <%d> больше высоты изображения.\n", y3);
        if (y3 < 0)
            printf("\tКоордината по вертикальной оси, задающая левый верхний угол, <%d> принимает отрицательное значение.\n", y3);
        printf("\tРазмеры изображения:\n");
        printf("\t\tВысота\t%u\n", H);
        printf("\t\tШирина\t%u\n\n", W);
        return;
    }
    int h = 0;
    int w = 0;
    if (W - x3 < x2 - x1)
        w = abs(W - x3 + 1); 
    else
        w = abs(x2-x1+1);
    if (y3 < y1 - y2)
        h = y3;
    else
        h = y1-y2+1;
    Rgb** copymas = malloc(h*sizeof(Rgb*));
    for (int i=0; i < h; i++){
        copymas[i] = malloc(w*sizeof(Rgb));
    }
    int x = 0;
    int y = 0;
    for (int i = y2; i < y2+h-1; i++){
        x=0;
        for (int j = x1; j <= x1+w-1; j++){
            copymas[y][x] = img.arr[i][j];
            x++;
        }
        y++;
    }
    int ycopy = 0;
    int xcopy;
    for (int i=y3-y; i<y3; i++) {
        xcopy = 0;
        for (int j = x3; j < x3 + x; j++) {
            img.arr[i][j] = copymas[ycopy][xcopy];
            xcopy++;
        }
        ycopy++;
    }
    free(copymas);
    writeFile(output_str, checki, &img);
}

int copy(image *img, int argc, char **argv, int opt, int longIndex){
    char input_str[50];
	strcpy(input_str, argv[1]);
    struct option longOptcopy[] = {
        {"start", required_argument, NULL, 's'},
        {"end", required_argument, NULL, 'e'},
        {"info", required_argument, NULL, 'i'},
        {"help", required_argument, NULL, 'h'},
        { NULL, 0, NULL, 0}
    };
    char *optscopy = "s:e:ih";
    char *output_str = argv[argc - 1];
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
    int correct = 0, checki = 0;
    opt = getopt_long(argc, argv, optscopy, longOptcopy, &longIndex);
    while(opt != -1){
        switch(opt){
            case 's':
                x1 = atoi(argv[optind-1]);
                y1 = atoi(argv[optind]);
                x2 = atoi(argv[optind+1]);
                y2 = atoi(argv[optind+2]);
                correct++;
                break;
            case 'e':
                x3 = atoi(argv[optind-1]);
                y3 = atoi(argv[optind]);
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
    if (correct == 2){
        copy_area(x1, y1, x2, y2, x3, y3, (int)img->bmih.width, (int)img->bmih.height, input_str, output_str, checki);
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