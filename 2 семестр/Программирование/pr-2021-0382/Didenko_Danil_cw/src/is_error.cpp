#include "class_images.h"

int images::is_error(){
    if(point[0][0] > image->width-1 || point[0][1] > image->height-1 ||
    point[2][0] > image->width-1 || point[2][1] > image->height-1 ||
    point[0][0] < 0 || point[0][1] < 0 || point[2][0] < 0 || point[2][1] < 0 ||
    point[0][0] > point[2][0] || point[0][1] > point[2][1]
            ){
        return 1;
    }
    return 0;
};
int images::is_error_R(){
    if(point[0][0] + R > image->width-1 || point[0][1] + R > image->height-1 ||
        point[0][0] - R < 0 || point[0][1] - R < 0 ||
        point[0][0] < 0 || point[0][1] < 0 || R <= 0){
        return 1;
    }
    return 0;
}

int images::is_error_Color(){
    if(RGBA[0] > 255 || RGBA[1] > 255 || RGBA[2] > 255 || RGBA[3] > 255 || RGBA[0] < 0 || RGBA[1] < 0 || RGBA[2] < 0 || RGBA[3] < 0){
        return 1;
    }
    return 0;
}

int images::is_error_Color_Fill(){
    if(RGBA_Fill[0] > 255 || RGBA_Fill[1] > 255 || RGBA_Fill[2] > 255 || RGBA_Fill[3] > 255 || RGBA_Fill[0] < 0 ||
    RGBA_Fill[1] < 0 || RGBA_Fill[2] < 0 || RGBA_Fill[3] < 0){
        return 1;
    }
    return 0;
}

