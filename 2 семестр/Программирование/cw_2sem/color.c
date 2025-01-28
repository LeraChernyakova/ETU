#include "allinfo.h"

int checkcolor(char *c){
    char *colors[] = {"Aqua", "Black", "Blue", "Fuchsia", "Gray", "Green", "Lime", "Maroon", "Navy", "Olive", "Purple", "Red", "Silver", "Teal", "White", "Yellow"};
    int check = -1;
    for (int i = 0; i < 16; i++){
        if (!strcmp(c, colors[i]))
            check = i;
    }
    return check;
}

void changecolor(int check, Rgb *c){
    switch(check){ 
        case 0:
            c->r = 0;
            c->g = 255;
            c->b = 255;
            break;
        case 1:
            c->r = 0;
            c->g = 0;
            c->b = 0; 
            break;      
        case 2:
            c->r = 0;
            c->g = 0;
            c->b = 255;
            break;
        case 3:
            c->r = 255;
            c->g = 0;
            c->b = 255;
            break;
        case 4:
            c->r = 128;
            c->g = 128;
            c->b = 128;
            break;
        case 5:
            c->r = 0;
            c->g = 128;
            c->b = 0;
            break;
        case 6:
            c->r = 0;
            c->g = 255;
            c->b = 0;
            break;
        case 7:
            c->r = 128;
            c->g = 0;
            c->b = 0;
            break;
        case 8:
            c->r = 0;
            c->g = 0;
            c->b = 128;
            break;
        case 9:
            c->r = 128;
            c->g = 128;
            c->b = 0;
            break;
        case 10:
            c->r = 128;
            c->g = 0;
            c->b = 128;
            break;
        case 11:
            c->r = 255;
            c->g = 0;
            c->b = 0;
            break;
        case 12:
            c->r = 192;
            c->g = 192;
            c->b = 192;
            break;
        case 13:
            c->r = 0;
            c->g = 128;
            c->b = 128;
            break;
        case 14:
            c->r = 255;
            c->g = 255;
            c->b = 255;
            break;
        case 15:
            c->r = 255;
            c->g = 255;
            c->b = 0;
            break;
    }
}



