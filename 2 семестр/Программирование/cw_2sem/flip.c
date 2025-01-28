#include "allinfo.h"

void flip_area(char* axis, int x1, int y1, int x2, int y2, unsigned int W, unsigned int H, char *input_str, char* output_str, int checki){
    image img;
    if (readFile(input_str, &img)){
        printHelp();
        return;
    }
    if (x1 > W || y1 > H || x1 < 0 || y1 < 0){
        printf("\x1b[31mОшибка -f/--flip!\nВыбранные координаты левого верхнего угла области находятся за пределами изображения.\x1b[0m\n\n");
        if (x1 > W)
            printf("\tКоордината по горизонтальной оси, задающая левый верхний угол, <%d> больше ширины изображения.\n", x1);
        if (x1 < 0)
            printf("\tКоордината по горизонатальной оси, задающая левый верхний угол, <%d> принимает отрицательное значение.\n", x1);
        if (y1 > H)
            printf("\tКоордината по вертикальной оси, задающая левый верхний угол, <%d> больше высоты изображения.\n", y1);
        if (y1 < 0)
            printf("\tКоордината по вертикальной оси, задающая левый верхний угол, <%d> принимает отрицательное значение.\n", y1);
        printf("\tРазмеры изображения:\n");
        printf("\t\tВысота\t%u\n", H);
        printf("\t\tШирина\t%u\n\n", W);
        return;
    }
    if (x2 > W || y2 > H || x2 < 0 || y2 < 0){
        printf("\x1b[31mОшибка -f/--flip!\nВыбранные координаты правого нижнего угла области находятся за пределами изображения.\x1b[0m\n\n");
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
        printf("\n\x1b[31mОшибка -f/--flip!\nКоордината х = %d правого нижнего угла должна быть больше координаты х  = %d левого верхнего угла.\x1b[0m\n\n", x2, x1);
        return;
    }
    if (y2 > y1){
        printf("\n\x1b[31mОшибка -f/--flip!\nКоордината y = %d правого нижнего угла должна быть меньше координаты y = %d левого верхнего угла.\x1b[0m\n\n", y2, y1);
        return;
    }

    Rgb pix;
    if (!strcmp(axis, "x")){
        for (int i = y2; i <= (y1+y2)/2; i++){
            for (int j = x1; j <= x2; j++){
                pix = img.arr[i][j];
                img.arr[i][j] = img.arr[y2+y1-i-1][j];
                img.arr[y2+y1-1-i][j] = pix;
            }
        }
    }
    else if (!strcmp(axis, "y")){
        for (int i = y2; i < y1; i++) {
            for (int j = x1; j <= (x1 + x2) / 2; j++) {
                pix = img.arr[i][j];
                img.arr[i][j] = img.arr[i][x1 + x2 - j];
                img.arr[i][x1 + x2 - j] = pix;
            }
        }
    }
    writeFile(output_str, checki, &img);
}

int flip(image *img, int argc, char **argv, int opt, int longIndex){
    char input_str[50];
	strcpy(input_str, argv[1]);
    struct option longOptflip[] = {
        {"leftlocation", required_argument , NULL, 'l'},
        {"rightlocation", required_argument, NULL, 'r'},
        {"axis", required_argument, NULL, 'a'},
        {"info", required_argument, NULL, 'i'},
        {"help", required_argument, NULL, 'h'},
        { NULL, 0, NULL, 0}
    };
    char *optsflip = "l:r:a:ih";
    char *output_str = argv[argc - 1];
    char *axis = malloc(20*sizeof(char));
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    int correct = 0, checki = 0;
    opt = getopt_long(argc,argv,optsflip,longOptflip,&longIndex);
    while(opt!=-1){
        switch(opt){
            case 'l':
                x1 = atoi(argv[optind-1]);
                y1 = atoi(argv[optind]);
                correct++;
                break;
            case 'r':
                x2 = atoi(argv[optind-1]);
                y2 = atoi(argv[optind]);
                correct++;
                break;
            case 'a':
                strcpy(axis, optarg);
                if (!strcmp(axis,"x") || !strcmp(axis,"y")){
                    correct++;
                }
                else{
                    printf("\x1b[31mОшибка -f/--flip!\nВыбранная ось %s недоступна.\x1b[0m\n\n", axis);
                    printf("Доступные оси для отражения изображения:\n");
                    printf("\tВертикальная - задается y;\n");
                    printf("\tГоризонтальная - задается x.\n\n");
                    return -1;
                }
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
        opt = getopt_long(argc,argv,optsflip,longOptflip,&longIndex);
    }
    if (correct == 3){
        flip_area(axis, x1, y1, x2, y2,(int)img->bmih.width, (int)img->bmih.height, input_str, output_str, checki);
    }
    else if(correct == -1){
        printf("\x1b[31mВведите один из ключей, чтобы увидеть меню программы: -h/--help.\x1b[0m\n\n");
        exit(0);
    }
    else{
        printf ("\n\x1b[31mОшибка -f/--flip!\nВведено слишком мало аргументов для работы функции.\x1b[0m\n");
        printf("\x1b[31mВведите один из ключей, чтобы увидеть меню программы: -h/--help.\x1b[0m\n\n");
        exit(0);
    }
    free(axis);
    return opt;
}