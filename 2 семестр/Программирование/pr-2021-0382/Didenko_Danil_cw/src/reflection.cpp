#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "class_images.h"
#include <png.h>

void images::reflection() {
    if (is_error()){
        std::cout<<"Wrong coоrdinates\n";
        exit(0);
    }
    int left_h = point[0][1], rigth_h = point[2][1], left_w = point[0][0], rigth_w = point[2][0];

    if(Ax == 0){
        for (int y = left_h; y < rigth_h; y++) {
            png_byte *row = image->row_pointers[y];
            for (int x = left_w; x < rigth_w/2; x++) {
                png_byte *ptr_beg = &(row[x * 4]);
                png_byte *ptr_eng = &(row[(rigth_w - x - 1) * 4]);
                for(int i = 0;i < 4;i++){
                    png_byte ptr_swap;
                    ptr_swap = ptr_beg[i];
                    ptr_beg[i] = ptr_eng[i];
                    ptr_eng[i] = ptr_swap;
                }
            }
        }

    }else if (Ax == 1){
        for (int y = left_h; y < rigth_h/2; y++) {
            png_byte *row_beg = image->row_pointers[y];
            png_byte *row_end = image->row_pointers[rigth_h - y - 1];
            for (int x = left_w; x < rigth_w; x++) {
                png_byte *ptr_beg = &(row_beg[x * 4]);
                png_byte *ptr_eng = &(row_end[x * 4]);
                for (int i = 0; i < 4; i++) {
                    png_byte ptr_swap;
                    ptr_swap = ptr_beg[i];
                    ptr_beg[i] = ptr_eng[i];
                    ptr_eng[i] = ptr_swap;
                }
            }
        }
    }else{
        std::cout << "Don't choose axis\n";
        exit(0);
    }
}

