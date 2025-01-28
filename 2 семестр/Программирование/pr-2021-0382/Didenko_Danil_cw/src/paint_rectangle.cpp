#include <iostream>
#include <png.h>
#include "class_images.h"

void images::paint_rectangle(){
    point[1][0] = point[2][0];
    point[1][1] = point[0][1];
    point[3][0] = point[0][0];
    point[3][1] = point[2][1];

    if (is_error()){
        std::cout<<"Wrong coоrdinates\n";
        exit(0);
    }

    if((bold > (point[3][1]-point[0][1]) || bold > (point[1][0]-point[3][0])) && bold != 0){
        std::cerr << "Too bold board\n";
        exit(0);
    }

    if(fill == 1){
        if (is_error_Color_Fill()){
            std::cout<<"Wrong color fill\n";
            exit(0);
        }
        int paint;
        if((point[3][1]-point[0][1]) >= (point[3][0]-point[1][0])){
            paint = (point[3][1]-point[0][1])/2+1;
        }else{
            paint = (point[3][0]-point[1][0])/2+1;
        }

        for(int i = 0; i < paint; i++){
            drawLine_Fill(point[0][0],point[0][1]+i,point[1][0],point[1][1]+i);
            drawLine_Fill(point[1][0]-i,point[1][1],point[2][0]-i,point[2][1]);
            drawLine_Fill(point[2][0],point[2][1]-i,point[3][0],point[3][1]-i);
            drawLine_Fill(point[3][0]+i,point[3][1],point[0][0]+i,point[0][1]);
        }
    }


    if (is_error_Color()){
        std::cout<<"Wrong color\n";
        exit(0);
    }

     for(int i = 0; i < bold; i++){
         drawLine(point[0][0],point[0][1]+i,point[1][0],point[1][1]+i);
         drawLine(point[1][0]-i,point[1][1],point[2][0]-i,point[2][1]);
         drawLine(point[2][0],point[2][1]-i,point[3][0],point[3][1]-i);
         drawLine(point[3][0]+i,point[3][1],point[0][0]+i,point[0][1]);
     }
}