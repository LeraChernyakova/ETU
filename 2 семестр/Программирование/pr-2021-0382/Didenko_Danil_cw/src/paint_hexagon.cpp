#include <iostream>
#include "class_images.h"

void images::paint_hexagon(){

    if(center[0] < 0 || center[1] < 0 || R <= 0){
        if((point[2][0] - point[0][0]) != (point[2][1] - point[0][1])){
            std::cerr<<"Coordinates state not square\n";
            exit(0);
        }
        center[0] = point[0][0] + (point[2][0] - point[0][0])/2;
        center[1] = point[0][1] + (point[2][1] - point[0][1])/2;
        R = (point[2][0] - point[0][0])/2;
    }

    point[0][0] = center[0];
    point[0][1] = center[1];

    R = R % 2 == 0 ? R: R-1;

    if(bold < 1 ){
        std::cerr << "Enter bold\n";
        exit(0);
    }
    if(R < 1){
        std::cerr << "Enter radius\n";
        exit(0);
    }

    if(bold > R){
        std::cerr << "Too bold board\n";
        exit(0);
    }

    int X1 = point[0][0],Y1 = point[0][1];
    int x = 0;
    int y = R;
    int delta = 1 - 2 * R;
    int error = 0;
    point[1][0] = X1+R;
    point[1][1] = Y1;
    int X2 = point[1][0],Y2 = point[1][1];
    //Точки для шестиугольника
    point[0][0] = X1+R;
    point[0][1] = Y1;
    point[1][0] = X1-R;
    point[1][1] = Y1;

    // Чтобы построить правильный шестиугольник, воспользуемся алгоритмом Евклида, использующего
    // точки пересечения окружностей, точки пересечения найдем с помощью алгоритма Брезенхема.

    while (y >= x){
        if((X1 + x) == (X2 - x) && (Y1 + y) == (Y2 + y)){
            point[2][0] = X1 + x;
            point[2][1] = Y1 + y;
            point[3][0] = X1 + x;
            point[3][1] = Y1 - y;
            point[4][0] = X1 - x;
            point[4][1] = Y1 + y;
            point[5][0] = X1 - x;
            point[5][1] = Y1 - y;
            break;
        }
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)){
            delta += 2 * ++x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)){
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - --y);
    }

    if(point[3][1] < 0 || point[2][1] > image->height-1 || point[0][0] > image->width-1 || point[1][0] < 0){
        std::cout<<"Wrong coоrdinates\n";
        exit(0);
    }

    if(fill == 1){
        if(RGBA_Fill[0] == -1 || RGBA_Fill[0] == -1 || RGBA_Fill[0] == -1 || RGBA_Fill[0] == -1){
            std::cout<<"Enter correct color\n";
            exit(0);
        }
        if (is_error_Color_Fill()){
            std::cout<<"Wrong color\n";
            exit(0);
        }

        int paint = R;
        for(int i = 0;i < paint; i++){
            drawLine_Fill(point[0][0]-i,point[0][1],point[3][0]-i,point[3][1]);
            drawLine_Fill(point[3][0],point[3][1]+i,point[5][0],point[5][1]+i);
            drawLine_Fill(point[5][0]+i,point[5][1],point[1][0]+i,point[1][1]);
            drawLine_Fill(point[1][0]+i,point[1][1],point[4][0]+i,point[4][1]);
            drawLine_Fill(point[4][0],point[4][1]-i,point[2][0],point[2][1]-i);
            drawLine_Fill(point[2][0]-i,point[2][1],point[0][0]-i,point[0][1]);
        }
    }

    if (is_error_Color()){
        std::cout<<"Wrong color\n";
        exit(0);
    }

    //Рисуем шестиугольник
    for(int i = 0;i < bold; i++){
        drawLine(point[0][0]-i,point[0][1],point[3][0]-i,point[3][1]);
        drawLine(point[3][0],point[3][1]+i,point[5][0],point[5][1]+i);
        drawLine(point[5][0]+i,point[5][1],point[1][0]+i,point[1][1]);
        drawLine(point[1][0]+i,point[1][1],point[4][0]+i,point[4][1]);
        drawLine(point[4][0],point[4][1]-i,point[2][0],point[2][1]-i);
        drawLine(point[2][0]-i,point[2][1],point[0][0]-i,point[0][1]);
    }
};