#ifndef CW_IMAGE_H
#define CW_IMAGE_H
#include <png.h>

class images{
private:
    char header[8];
    struct Png{
        int width, height;
        png_byte color_type;
        png_byte bit_depth;
        png_structp png_ptr;
        png_infop info_ptr;
        int number_of_passes;
        png_bytep *row_pointers;
    };
    int point[6][2] = {{0,0},{0,0},{-1,-1},{0,0},{0,0},{0,0}};
    struct Png* image = new struct Png;
    int RGBA[4] = {-1,-1,-1,-1};
    int RGBA_Fill[4] = {-1,-1,-1,-1};
    int center[2] = {-1,-1};
    int bold = 0;
    int fill = 0;
    int R = 0;
    int Ax = -1;
public:
    ~images(){
        delete image;
    }
    void read_png_file(char *file_name);
    void write_png_file(char *file_name);
    void drawpixel(int x,int y);
    void drawpixel_Fill(int x,int y);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawLine_Fill(int x1, int y1, int x2, int y2);
    void reflection();
    void paint_pentogram();
    void paint_rectangle();
    void paint_hexagon();

    int is_error();
    int is_error_R();
    int is_error_Color();
    int is_error_Color_Fill();
    struct Png* get_info(){
        return image;
    };

    void set_center(int x1, int y1){
        center[0] = x1;
        center[1] = y1;
    }
    void set_point(int N, int x1, int y1){
        point[N][0] = x1;
        point[N][1] = y1;
    }
    void set_axis(int a){
        Ax = a;
    }
    void set_radius(int a){
        R = a;
    }
    void set_color(int i, int c){
        RGBA[i] = c;
    }
    void set_color_fill(int i, int c){
        RGBA_Fill[i] = c;
    }
    void set_bold(int b){
        bold = b;
    }
    void set_fill(int f){
        fill = f;
    }
};

#endif //CW_IMAGE_H
