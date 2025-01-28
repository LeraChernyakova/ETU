#include <cstdlib>
#include <iostream>
#include "class_images.h"
#include <getopt.h>
#include <unistd.h>
#include <cstring>


int main(int argc, char **argv) {
    static int function_flag = 0;
    char* name_out_file = argv[argc-1];
    images image;
    image.read_png_file(argv[1]);
    int c;
    while (1)
    {
        static struct option long_options[] =
                {       {"help",no_argument,0, 'H'},
                        {"info",no_argument,0, 'i'},
                        {"reflection",no_argument,0, 'r'},
                        {"pentograma",no_argument,0,'p'},
                        {"rectangle",no_argument,0,'t'},
                        {"hexagon",no_argument,0,'h'},
                        {"center",required_argument,0,'c'},
                        {"start",required_argument,0, 's'},
                        {"end",  required_argument,0, 'e'},
                        {"radius",required_argument,0,'R'},
                        {"bold_board",required_argument,0,'b'},
                        {"color_board",required_argument,0,'B'},
                        {"fill",no_argument,0,'f'},
                        {"color_fill",required_argument,0,'F'},
                        {"vertical", no_argument,0,'V'},
                        {"horizontal", no_argument,0,'Z'},
                        {"save", required_argument,0,'S'},
                        {0, 0, 0, 0}
                };
        static int option_index = 0;
        c = getopt_long (argc, argv, "iHrpthc:s:e:R:b:B:fF:ZVS:", long_options, &option_index);
        if (c == -1)
            break;
        switch (c)
        {
            case 'H':
                function_flag = 0;
                std::cout << "--info\tНе требует аргументов, сокращенный ключ -i. Показывает информацию об изображении\n\n";
                std::cout << "--help\tНе требует аргументов, сокращенный ключ -H. Показывает возможные команды\n\n";
                std::cout << "--reflection\tНе требует аргументов, сокращенный ключ -r. Отражает выбранную области изображения,"
                             " параметры области: координаты левого верхнего угла, координаты нижнего правого угла, ось отражения\n\n";
                std::cout << "--pentograma\tНе требует аргументов, сокращенный ключ -p. Рисует пентограмму в круге в пределах границ изображения."
                             "Параметры: координаты центра круга,радиус круга, толщина линий, цвет линий.\n\n";
                std::cout << "--rectangle\tНе требует аргументов, сокращенный ключ -t. Рисует прямоугольник в пределах границ изображения."
                             "Параметры: координаты левого верхнего угла фигуры, координаты правого нижнего угла фигуры, толщина линии, цвет линии, есть ли заливка, цвет заливки.\n\n";
                std::cout << "--hexagon\tНе требует аргументов, сокращенный ключ -h. Рисует правильный шестиугольник в пределах границ изображения."
                             "Параметры: координаты центра описанной окружности,радиус окружности, толщина линий, цвет линий, есть ли заливка, цвет заливки.\n\n";
                std::cout << "--start\tСокращенный ключ -s. Аргументы: <координата по X левой верхней точки> <координата по Y левой верхней точки>.\n\n";
                std::cout << "--end\tСокращенный ключ -e. Аргументы: <координата по X правой нижней точки> <координата по Y правой нижней точки>.\n\n";
                std::cout << "--radius\tСокращенный ключ -R. Аргументы <радиус описанной окружности>.\n\n";
                std::cout << "--bold_board\tСокращенный ключ -b. Аргументы: <толщина линий фигуры>.\n\n";
                std::cout << "--color_board\tСокращенный ключ -B. Аргументы: <0-255 Красный> <0-255 Зеленый> <0-255 Синий> <0-255 Альфа-канал>.\n\n";
                std::cout << "--fill\tНе требует аргументов. Указывает, есть ли заливка у фигуры.\n\n";
                std::cout << "--color_fill\tСокращенный ключ -F. Аргументы: <0-255 Красный> <0-255 Зеленый> <0-255 Синий> <0-255 Альфа-канал>.\n\n";
                std::cout << "--vertical\tНе требует аргументов, сокращенный ключ -V. Устанавливает вертикальное отражение.\n\n";
                std::cout << "--horizontal\tНе требует аргументов, сокращенный ключ -Z. Устанавливает горизонтальное отражение.\n\n";
                std::cout << "--save\tСокращенный ключ -S. Аргументы: имя сохраняемого файла.\n\n";
                break;
            case 'i':
                std::cout << "Ширина в пикселях: " <<image.get_info()->width << "\n";
                std::cout << "Высота в пикселях: " <<image.get_info()->height << "\n";
                printf("Тип цвета: %u\n", image.get_info()->color_type);
                printf("Глубина цвета: %u бит\n", image.get_info()->bit_depth);
                break;
            break;
            case 'r':
                function_flag = 1;
                break;
            case 'p':
                function_flag = 2;
                break;
            case 't':
                function_flag = 3;
                break;
            case 'h':
                function_flag = 4;
                break;
            case 'c':
                if(optind > argc){
                    break;
                }
                image.set_center(atoi(optarg)-1,atoi(argv[optind])-1);
                break;
            case 's':
                if(optind > argc){
                    break;
                }
                image.set_point(0,atoi(optarg)-1,atoi(argv[optind])-1);
                break;
            case 'e':
                if(optind >= argc){
                    break;
                }
                image.set_point(2,atoi(optarg)-1,atoi(argv[optind])-1);
                break;
            case 'R':
                image.set_radius(atoi(optarg));
                break;
            case 'b':
                image.set_bold(atoi(optarg));
                break;
            case 'B':
                image.set_color(0, atoi(optarg));
                for(int i = 1;i < 4; i++){
                    if(optind >= argc){
                        std::cerr << "Too few color arguments\n";
                        exit(0);
                    }
                    if(argv[optind][0] != '0' && atoi(argv[optind]) == 0){
                        std::cerr << "Too few color arguments\n";
                        exit(0);
                    };
                    image.set_color(i,atoi(argv[optind]));
                    optind++;
                }
                break;
            case 'f':
                image.set_fill(1);
                break;
            case 'F':
                image.set_color_fill(0, atoi(optarg));
                for(int i = 1;i < 4; i++){
                    if(optind >= argc){
                        std::cerr << "Too few color arguments\n";
                        exit(0);
                    }
                    if(argv[optind][0] != '0' && atoi(argv[optind]) == 0){
                        std::cerr << "Too few color arguments\n";
                        exit(0);
                    };
                    image.set_color_fill(i,atoi(argv[optind]));
                    optind++;
                }
                break;
            case 'V':
                image.set_axis(0);
                break;
            case 'Z':
                image.set_axis(1);
                break;
            case 'S':
                name_out_file = optarg;
                break;
            case '?':
                break;
            default:
                abort();
        }
        option_index++;
    }
        switch (function_flag) {
            case 1:
                image.reflection();
                image.write_png_file(name_out_file);
                break;
            case 2:
                image.paint_pentogram();
                image.write_png_file(name_out_file);
                break;
            case 3:
                image.paint_rectangle();
                image.write_png_file(name_out_file);
                break;
            case 4:
                image.paint_hexagon();
                image.write_png_file(name_out_file);
                break;
        case 0:
                break;
            default:
                printf("Function doesn't choose\n");
        }

    return 0;
}
