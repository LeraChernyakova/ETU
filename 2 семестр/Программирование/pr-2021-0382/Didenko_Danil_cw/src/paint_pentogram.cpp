#include <iostream>
#include <cstdlib>
#include <png.h>
#include "class_images.h"



void images::drawpixel(int x,int y){
    png_byte *row = image->row_pointers[y];
    for(int i = 0;i < 4;i++){
        row[x*4+i] = RGBA[i];
    }
}

void images::drawpixel_Fill(int x,int y){
    png_byte *row = image->row_pointers[y];
    for(int i = 0;i < 4;i++){
        row[x*4+i] = RGBA_Fill[i];
    }
}

void images::drawLine(int x1, int y1, int x2, int y2) {
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    drawpixel(x2,y2);
    while(x1 != x2 || y1 != y2)
    {
        drawpixel(x1,y1);
        int error2 = error * 2;
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

void images::drawLine_Fill(int x1, int y1, int x2, int y2) {
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    drawpixel_Fill(x2,y2);
    while(x1 != x2 || y1 != y2)
    {
        drawpixel_Fill(x1,y1);
        int error2 = error * 2;
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

void images::paint_pentogram(){

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

    if(bold > R/2){
        std::cout<<"Too bold board\n";
        exit(0);
    }
    if (is_error_R()){
        std::cout<<"Wrong coоrdinates\n";
        exit(0);
    }
    if (is_error_Color()){
        std::cout<<"Wrong color\n";
        exit(0);
    }



    // для рисования круга используем алгоритм Брезенхема
    int X1 = center[0],Y1 = center[1];
    int x = 0;
    int y = R;
    int delta = 1 - 2 * R;
    int error = 0;

    //Точки для пентограммы
    point[0][0] = X1;
    point[0][1] = Y1-R+bold;

    //Рисование круга
    while (y >= x){
        if(x == R/2){
            point[2][0] = X1-(R)+bold;
            point[2][1] = Y1-(R-y);
            point[3][0] = X1+(R)-bold;
            point[3][1] = Y1-(R-y);
        }
        if(x == R/2){
            point[1][0] = X1+x;
            point[1][1] = Y1+y-bold;

            point[4][0] = X1-x;
            point[4][1] = Y1+y-bold;
        }
        for(int i = 0; i < bold;i++){
            drawpixel(X1 + x, Y1 + y-i);
            drawpixel(X1 + x, Y1 - y+i);
            drawpixel(X1 - x, Y1 + y-i);
            drawpixel(X1 - x, Y1 - y+i);
            drawpixel(X1 + y-i, Y1 + x);
            drawpixel(X1 + y-i, Y1 - x);
            drawpixel(X1 - y+i, Y1 + x);
            drawpixel(X1 - y+i, Y1 - x);
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


    //Рисование пентограммы в круге
    for(int i = 0; i < bold;i++){
        drawLine(point[0][0]+i,point[0][1],point[1][0]+i,point[1][1]);
        drawLine(point[1][0],point[1][1]+i,point[2][0],point[2][1]+i);
        drawLine(point[2][0],point[2][1]-i,point[3][0],point[3][1]-i);
        drawLine(point[3][0],point[3][1]+i,point[4][0],point[4][1]+i);
        drawLine(point[4][0]-i,point[4][1],point[0][0]-i,point[0][1]);
    }


}
