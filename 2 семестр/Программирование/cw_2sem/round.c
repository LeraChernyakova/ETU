#include "allinfo.h"

void width(Rgb** arr, int x, int y, int w, int H, int W, unsigned char r, unsigned char g, unsigned char b){
	int l = w/2;
	for(int i = x - l; i <= x+l; i++){
		for(int j = y - l; j <= y + l; j++){
			if((i >= 0) && (i < H) && (j >= 0)&& (j < W)&&(pow(x-i,2)+pow(y-j,2) <= pow(l,2))){
                arr[i][j].r = r;
                arr[i][j].g = g;
                arr[i][j].b = b;
            }
		}
	}
}

void drawRing(Rgb** arr, unsigned int H, unsigned int W, int R, int x0, int y0, int w, unsigned char r, unsigned char g, unsigned char b){
    if(((x0-R) < 0) || ((y0-R) < 0) || ((R+x0) > W) || ((R+y0) > H)){
        printf("\n\x1b[31mОшибка -r/--round!\nВведеное значение радиуса окружности находится за пределами изображения:\x1b[0m\n");
        if ((R+x0) > W)
            printf("\tРадиус <%d> окружности с центром в точках x - <%d>, y - <%d> больше ширины изображения.\n", R, x0, y0);
        if ((x0-R) < 0)
            printf("\tРадиус <%d> окружности с центром в точках x - <%d>, y - <%d> выходит за пределы изображения.\n", R, x0, y0);
        if ((R+y0) > H)
            printf("\tРадиус <%d> окружности с центром в точках x - <%d>, y - <%d> больше высоты изображения.\n", R, x0, y0);
        if ((y0-R) < 0)
            printf("\tРадиус <%d> окружности с центром в точках x - <%d>, y - <%d> выходит за пределы изображения.\n", R, x0, y0);
        printf("\tРазмеры изображения:\n");
        printf("\t\tВысота\t%u\n", H);
        printf("\t\tШирина\t%u\n\n", W);
        return;       
    } 
    if (R <= 0){
        printf("\n\x1b[31mОшибка -r/--round!\nЗначение радиуса окружности <%d> не является натуральным числом.\x1b[0m\n\n", R);
        return;
    }
    if (w < 0){
        printf("\n\x1b[31mОшибка -r/--round!\nЗначение толщины окружности <%d> принимает отрицательное значение.\x1b[0m\n\n", w);
        return;
    }
    int x = 0;
    int y = R;
	int del = 1 - 2*R;
	int error = 0;

    if (w != 0){
        while(y >= x){
            width(arr, y0+x, x0+y, w, H, W, r, g, b);
		    width(arr, y0+x, x0-y, w, H, W, r, g, b);
		    width(arr, y0-x, x0+y, w, H, W, r, g, b);
		    width(arr, y0-x, x0-y, w, H, W, r, g, b);
		    width(arr, y0+y, x0+x, w, H, W, r, g, b);
		    width(arr, y0+y, x0-x, w, H, W, r, g, b);
		    width(arr, y0-y, x0+x, w, H, W, r, g, b);
		    width(arr, y0-y, x0-x, w, H, W, r, g, b);	
		    error = 2 *(del + y) - 1;
		    if((error <= 0) && (del < 0)){
			    x++;
			    del += 2 * x + 1;
			    continue;
		    }
		    if(del > 0 && error > 0){
			    --y;
			    del += 1 - 2 * y;
			    continue;
		    }
		    ++x;
		    --y;
		    del += 2 * (x - y);
        }
    }
    else{
        printf ("\nВы не выбрали значение толщины окружности. Толщина по умолчанию - 1 пиксель.\n\n");
        int wid = 1;
        while(y >= x){
            width(arr, y0+x, x0+y, wid, H, W, r, g, b);
		    width(arr, y0+x, x0-y, wid, H, W, r, g, b);
		    width(arr, y0-x, x0+y, wid, H, W, r, g, b);
		    width(arr, y0-x, x0-y, wid, H, W, r, g, b);
		    width(arr, y0+y, x0+x, wid, H, W, r, g, b);
		    width(arr, y0+y, x0-x, wid, H, W, r, g, b);
		    width(arr, y0-y, x0+x, wid, H, W, r, g, b);
		    width(arr, y0-y, x0-x, wid, H, W, r, g, b);	
		    error = 2 *(del + y) - 1;
		    if((error <= 0) && (del < 0)){
			    x++;
			    del += 2 * x + 1;
			    continue;
		    }
		    if(del > 0 && error > 0){
			    --y;
			    del += 1 - 2 * y;
			    continue;
		    }
		    ++x;
		    --y;
		    del += 2 * (x - y);
        }
    }
}

int checkColorLine(Rgb *elem, unsigned char rl, unsigned char gl, unsigned char bl){
	if ((elem -> b == bl) && (elem -> r == rl) && (elem -> g == gl))
		return 1;
	else
		return 0;
}

int checkColorFill(Rgb *elem, unsigned char rf, unsigned char gf, unsigned char bf){
	if ((elem -> b == bf) && (elem -> r == rf) && (elem -> g == gf))
		return 1;
	else
		return 0;
}

void ChangeColorFill(Rgb *elem, unsigned char rf, unsigned char gf, unsigned char bf){
	elem -> b = bf;
	elem -> r = rf;
	elem -> g = gf;
}

void fill(int x, int y, Rgb **arr, unsigned char rl, unsigned char gl, unsigned char bl, unsigned char rf, unsigned char gf, unsigned char bf){
	ChangeColorFill(&arr[x][y], rf, gf, bf);
	if ((checkColorFill(&arr[x+1][y], rf, gf, bf) == 0) && (checkColorLine(&arr[x+1][y], rl, gl, bl)) == 0)
		fill(x+1, y, arr, rl, gl, bl, rf, gf, bf);
	if ((checkColorFill(&arr[x][y+1], rf, gf, bf) == 0) && (checkColorLine(&arr[x][y+1], rl, gl, bl)) == 0)
		fill(x, y+1, arr, rl, gl, bl, rf, gf, bf);
	if ((checkColorFill(&arr[x-1][y], rf, gf, bf) == 0) && (checkColorLine(&arr[x-1][y], rl, gl, bl)) == 0)
		fill(x-1, y, arr, rl, gl, bl, rf, gf, bf);
	if ((checkColorFill(&arr[x][y-1], rf, gf, bf) == 0) && (checkColorLine(&arr[x][y-1], rl, gl, bl)) == 0)
		fill(x, y-1, arr, rl, gl, bl, rf, gf, bf);	
}

void drawCircle(Rgb **arr, unsigned int H, unsigned int W, int R, int x0, int y0, int w, unsigned char rl, unsigned char gl, unsigned char bl, unsigned char rf, unsigned char gf, unsigned char bf){
    drawRing(arr,H,W,R,x0,y0,w,rl,gl,bl);
    fill(x0,y0,arr,rl,gl,bl,rf,gf,bf);
}


int roundopt(image *img, int argc, char **argv, int opt, int longIndex){
    char input_str[50];
	strcpy(input_str, argv[1]);
    struct option longOptround[] = {
        {"locationcenter", required_argument, NULL, 'l'},
        {"locationsquare", required_argument, NULL, 's'},
        {"Radius", required_argument, NULL, 'R'},
        {"width", required_argument,NULL, 'w'},
        {"colorline", required_argument, NULL, 'c'},
        {"colorfill", required_argument, NULL, 'C'},
        {"fill", required_argument, NULL, 'f'},
        {"info", required_argument, NULL, 'i'},
        {"help", required_argument, NULL, 'h'},
        { NULL, 0, NULL, 0}
    };
    char *optsround = "rl:s:R:w:c:C:f:ih";
    char *output_str = argv[argc - 1];
    char *fill = malloc(20*sizeof(char));
    char *colorl = malloc(20*sizeof(char));
    char *colorf = malloc(20*sizeof(char));
    Rgb line;
    Rgb pour;
    int x0 = -1, y0 = -1, R = -1, x1 = -1, y1 = -1, xl = -1, yl = -1, w = 0, rl = 0, gl = 0,
    bl = 0, f = 0, rf = 0, gf = 0, bf = 0;
    int intcl = -2, intcf = -2;
    int checkr = 0, checksq = 0, checkl = 0, checkf = 0, checki = 0;
    int correct = 0;
    opt = getopt_long(argc,argv,optsround,longOptround,&longIndex);
    while(opt!=-1){
        switch(opt){
            case 's':
                if (checkl != 0){
                    printf("\x1b[31m\nОшибка! Вы уже ввели координаты центра окружности. Выберете либо координаты центра и радиус либо координаты квадрата.\x1b[0m\n");
                    return -1;
                }
                else if (checkr != 0){
                    printf("\x1b[31m\nОшибка! Вы уже ввели значение радиуса! Выберете либо координаты центра и радиус либо координаты квадрата!\x1b[0m\n");
                    return -1;
                }
                x0 = atoi(argv[optind-1]);
                y0 = atoi(argv[optind]);
                x1 = atoi(argv[optind+1]);
                y1 = atoi(argv[optind+2]);
                checksq = 1;
                if (x1 >= (int)img->bmih.width || y0 >= (int)img->bmih.height || x0 < 0 || y1 < 0){
                    printf("\n\x1b[31mОшибка -r/--round!\nВыбранные координаты центра окружности находятся за пределами изображения:\x1b[0m\n");
                    if (x1 >= (int)img->bmih.width)
                        printf("\tКоордината, задающая правый нижний угол квадрата по горизонтальной оси, <%d> больше ширины изображения.\n", x1);
                    if (x0 < 0)
                        printf("\tКоордината, задающая левый верхний угол квадрата по горизонтальной оси, <%d> принимает отрицательное значение.\n", x0);
                    if (y0 >= (int)img->bmih.height)
                        printf("\tКоордината, задающая правый нижний угол квадрата по вертикальной оси, <%d> больше высоты изображения.\n", y1);
                    if (y1 < 0)
                        printf("\tКоордината, задающая левый верхний угол квадрата по вертикальной оси, <%d> принимает отрицательное значение.\n", y0);
                    printf("\tРазмеры изображения:\n");
                    printf("\t\tВысота\t%d\n", (int)img->bmih.height);
                    printf("\t\tШирина\t%d\n\n", (int)img->bmih.width);
                    return -1;
                }
                if (x1 < x0){
                    printf("\n\x1b[31mОшибка -r/--round!\nКоордината х = %d правого нижнего угла должна быть больше координаты х  = %d левого верхнего угла.\x1b[0m\n\n", x1, x0);
                    return -1;
                }
                if (y1 > y0){
                    printf("\n\x1b[31mОшибка -r/--round!\nКоордината y = %d правого нижнего угла должна быть меньше координаты y = %d левого верхнего угла.\x1b[0m\n\n", y1, y0);
                    return -1;
                }
                if (x1-x0 != y0-y1){
                    printf("\n\x1b[31mОшибка -r/--round!\nВыбранная область не является квадратом.\x1b[0m\n");
                    printf("Размеры выбранной области:\n");
                    printf("\tВысота\t%d\n", x1-x0);
                    printf("\tШирина\t%d\n\n", y0-y1);
                    return -1;
                }
                break;
            case 'l':
                if (checksq != 0){
                    printf("\x1b[31m\nОшибка! Вы уже ввели координаты для квадрата, в который будет вписана окружность! Выберете либо координаты центра и радиус, либо координата квадрата!\n");
                    return -1;
                }
                xl = atoi(argv[optind-1]);
                yl = atoi(argv[optind]);
                checkl += 1;
                if (xl > (int)img->bmih.width || yl > (int)img->bmih.height || xl < 0 || yl < 0){
                    printf("\n\x1b[31mОшибка -r/--round!\nВыбранные координаты центра окружности находятся за пределами изображения:\x1b[0m\n");
                    if (xl > (int)img->bmih.width)
                        printf("\tКоордината, задающая центр окружности по горизонтальной оси, <%d> больше ширины изображения.\n", xl);
                    if (xl < 0)
                        printf("\tКоордината, задающая центр окружности по горизонтальной оси, <%d> принимает отрицательное значение.\n", xl);
                    if (yl > (int)img->bmih.height)
                        printf("\tКоордината, задающая центр окружности по вертикальной оси, <%d> больше высоты изображения.\n", yl);
                    if (yl < 0)
                        printf("\tКоордината, задающая центр окружности по вертикальной оси, <%d> принимает отрицательное значение.\n", yl);
                    printf("\tРазмеры изображения:\n");
                    printf("\t\tВысота\t%d\n", (int)img->bmih.height);
                    printf("\t\tШирина\t%d\n\n", (int)img->bmih.width);
                    return -1;
                }
                break;
            case 'R':
                if (checksq != 0){
                    printf("\x1b[31m\nОшибка! Вы уже ввели координаты для квадрата, в который будет вписана окружность! Выберете либо координаты центра и радиус, либо координата квадрата!\n");
                    return -1;
                }
                R = atoi(argv[optind-1]);
                checkr = 1;
                break;
            case 'w':
                w = atoi(argv[optind-1]);
                break;
            case 'f':
                strcpy(fill, optarg);
                if (!strcmp(fill, "yes")){
                    checkf = 1;
                }
                else if(!strcmp(fill,"no")){
                    checkf = -1;
                }
                else{
                    printf("\n\x1b[31mОшибка! Введено некорректное значение для выбора залита окружность или нет:\x1b[0m\n"
                    "Введите:\n"
                    "\tyes - чтобы залить окружность;\n"
                    "\tno - чтобы не заливать окружность.\n");
                    return -1;
                }
                break;
            case 'c':
                strcpy(colorl, optarg);
                if (checkcolor(colorl) != -1){
                    intcl = checkcolor(colorl);
                    changecolor(intcl, &line);
                    rl = line.r;
                    gl = line.g;
                    bl = line.b;
                }
                else{
                    printf ("\x1b[31m \nОшибка!\nВы выбрали недопустимый цвет для линий окружности. Попробуйте еще раз.\x1b[0m\n"
                    "\tДоступные цвета:\n"
                    "\t\t\tAqua(морская волна);\n"
                    "\t\t\tBlack(черный);\n"
                    "\t\t\tBlue(голубой);\n"
                    "\t\t\tFuchsia(фуксин);\n"
                    "\t\t\tGray(серый);\n"
                    "\t\t\tGreen(зеленый);\n"
                    "\t\t\tLime(ярко-зеленый);\n"
                    "\t\t\tMaroon(темно-бордовый);\n"
                    "\t\t\tNavy(темно-синий);\n"
                    "\t\t\tOlive(оливковый);\n"
                    "\t\t\tPurple(фиолетовый);\n"
                    "\t\t\tRed(красный);\n"
                    "\t\t\tSilver(серебряный);\n"
                    "\t\t\tTeal(серо-зеленый);\n"
                    "\t\t\tWhite(белый);\n"
                    "\t\t\tYellow(желтый).\n\n");
                    return -1;
                }
                break;
            case 'C':
                strcpy(colorf, optarg);
                if (checkcolor(colorf) != -1){
                    intcf = checkcolor(colorf);
                    changecolor(intcf, &pour);
                    rf = pour.r;
                    gf = pour.g;
                    bf = pour.b;
                }
                else{
                    printf ("\x1b[31m \nОшибка!\nВы выбрали недопустимый цвет для заливания окружности. Попробуйте еще раз.\x1b[0m\n"
                    "\tДоступные цвета:\n"
                    "\t\t\tAqua(морская волна);\n"
                    "\t\t\tBlack(черный);\n"
                    "\t\t\tBlue(голубой);\n"
                    "\t\t\tFuchsia(фуксин);\n"
                    "\t\t\tGray(серый);\n"
                    "\t\t\tGreen(зеленый);\n"
                    "\t\t\tLime(ярко-зеленый);\n"
                    "\t\t\tMaroon(темно-бордовый);\n"
                    "\t\t\tNavy(темно-синий);\n"
                    "\t\t\tOlive(оливковый);\n"
                    "\t\t\tPurple(фиолетовый);\n"
                    "\t\t\tRed(красный);\n"
                    "\t\t\tSilver(серебряный);\n"
                    "\t\t\tTeal(серо-зеленый);\n"
                    "\t\t\tWhite(белый);\n"
                    "\t\t\tYellow(желтый).\n\n");
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
        opt = getopt_long(argc,argv,optsround,longOptround,&longIndex);
    }
    int x = 0, y = 0, radius = 0;
    if (x1 > -1 && y1 > -1 && x0 > -1 && y0 > -1 && (xl == -1 && yl == -1 && R == -1)){
        x = x0+((x1-x0)/2);
        y = y1+((y0-y1)/2);
        radius = (x1-x0)/2;
    }
    else if((x1 == -1 && y1 == -1 && x0 == -1 && y0 == -1) && xl > -1 && yl > -1 && R > -1){
        x = xl;
        y = yl;
        radius = R;       
    } 
    if(checkf == 1 && correct != -1){
        if(intcl == -2 && intcf == -2){
            printf("\nВы не выбрали цвет линий окружности и заливки. Цвет линиий по умолчанию - черный. Цвет заливки по умолчанию - белый\n");
            changecolor(1, &line);
            rl = line.r;
            gl = line.g;
            bl = line.b;
            changecolor(14, &pour);
            rf = pour.r;
            gf = pour.g;
            bf = pour.b;
            drawCircle(img->arr,(int)img->bmih.height,(int)img->bmih.width, radius, x, y, w, rl, gl, bl, rf, gf, bf);
            writeFile(output_str, checki, img);
        }
        else if(intcl == -2){
            printf("\nВы не выбрали цвет линий окружности. Цвет линий по умолчанию - черный.\n");
            changecolor(1, &line);
            rl = line.r;
            gl = line.g;
            bl = line.b;
            drawCircle(img->arr,(int)img->bmih.height, (int)img->bmih.width, radius, x, y, w, rl, gl, bl, rf, gf, bf);
            writeFile(output_str, checki, img);
        }
        else if(intcf == -2){
            printf("\nВы не выбрали цвет для заливки окружности. Цвет заливки по умолчанию - белый.\n");
            changecolor(14, &pour);
            rf = pour.r;
            gf = pour.g;
            bf = pour.b;
            drawCircle(img->arr, (int)img->bmih.height, (int)img->bmih.width, radius, x, y,w, rl, gl, bl, rf, gf, bf);
            writeFile(output_str, checki, img);
        }
        else{
            drawCircle(img->arr, (int)img->bmih.height, (int)img->bmih.width, radius, x, y,w, rl, gl, bl, rf, gf, bf);
            writeFile(output_str, checki, img);
        }
    }
    else if(checkf == -1 && correct != -1){
        if (intcl != -2){
            drawRing(img->arr, (int)img->bmih.height, (int)img->bmih.width, radius, x, y , w, rl, gl, bl);
            writeFile(output_str, checki, img);
        }
        else {
            printf("\nВы не выбрали цвет линий окружности. Цвет линий по умолчанию - черный.\n");
            changecolor(1, &line);
            rl = line.r;
            gl = line.g;
            bl = line.b;
            drawRing(img->arr, (int)img->bmih.height, (int)img->bmih.width, radius, x, y , w, rl, gl, bl);
            writeFile(output_str, checki, img);
            }
    }
    else if(checkf == 0 && correct != -1){
        printf("\nВы не выбрали залита окружность или нет. По умолчанию окружность - не залита.\n");
        if (intcl != -2){
            drawRing(img->arr, (int)img->bmih.height, (int)img->bmih.width, radius, x, y , w, rl, gl, bl);
            writeFile(output_str, checki, img);
        }
        else {
            printf("\nВы не выбрали цвет линий окружности. Цвет линий по умолчанию - черный.\n");
            changecolor(1, &line);
            rl = line.r;
            gl = line.g;
            bl = line.b;
            drawRing(img->arr, (int)img->bmih.height, (int)img->bmih.width, radius, x, y , w, rl, gl, bl);
            writeFile(output_str, checki, img);
        }
    }
    else if(correct == -1){
        printf("\x1b[31mВведите один из ключей, чтобы увидеть меню программы: -h/--help.\x1b[0m\n\n");
        exit(0);
    }
    else{
        printf ("\n\x1b[31mОшибка -r/--round!\nВведено слишком мало аргументов для работы функции.\x1b[0m\n");
        printf("\x1b[31mВведите один из ключей, чтобы увидеть меню программы: -h/--help.\x1b[0m\n\n");
        exit(0);
    }
    free(fill);
    free(colorf);
    free(colorl);
    return opt;
}