#include "Image_PNG.h"
#include <QMessageBox>
#include <QFile>
#include <QtMath>


void Image_PNG::writeTempImgOnDisk(QString temp_path){
    std::string tmp_str =   temp_path.toStdString();
    const char *c_path = tmp_str.c_str();

    /* Открываем файл для бин. чтения*/
    FILE *fp = fopen(c_path, "wb");
    if (fp == NULL){
        // Some error handling: file could not be opened
        QMessageBox::critical(nullptr,"Ошибка","Файл с таким именем не найден");
        return ;
    }

    /* Выделение дин. памяти */
    m_png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (m_png_ptr == NULL){
        fclose(fp);
        // Some error handling: png_create_write_struct failed

        QMessageBox::critical(nullptr,"Ошибка","Не удалось выделить дин. память для структуры png_ptr");
        return ;
    }

    m_info_ptr = png_create_info_struct(m_png_ptr);
    if (m_info_ptr == NULL){
        png_destroy_write_struct(&m_png_ptr, NULL);
        fclose(fp);
        // Some error handling: png_create_info_struct failed

        QMessageBox::critical(nullptr,"Ошибка","Не удалось выделить дин. память для структуры info_ptr");
        return ;
    }

    if (setjmp(png_jmpbuf(m_png_ptr))){
        png_destroy_write_struct(&m_png_ptr, &m_info_ptr);
        fclose(fp);
        // Some error handling: error during init_io

        QMessageBox::critical(nullptr,"Ошибка","Произошла ошибка при записи информации о файле");
        return ;
    }

    png_init_io(m_png_ptr, fp);


    /* write header */
    if (setjmp(png_jmpbuf(m_png_ptr))){
        png_destroy_write_struct(&m_png_ptr, &m_info_ptr);
        fclose(fp);
        // Some error handling: error during writing header
    }

    png_set_IHDR(m_png_ptr, m_info_ptr, m_width, m_height,
                 m_bit_depth, m_color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(m_png_ptr, m_info_ptr);


    /* write bytes */
    if (setjmp(png_jmpbuf(m_png_ptr))){
        png_destroy_write_struct(&m_png_ptr, &m_info_ptr);
        fclose(fp);
        // Some error handling: error during writing bytes

        QMessageBox::critical(nullptr,"Ошибка","Произошла ошибка при записи изображения");
        return ;
    }

    png_write_image(m_png_ptr, m_arr_pixel);


    /* end write */
    if (setjmp(png_jmpbuf(m_png_ptr))){
        png_destroy_write_struct(&m_png_ptr, &m_info_ptr);
        fclose(fp);
        // Some error handling: error during end of write

        QMessageBox::critical(nullptr,"Ошибка","Произошла ошибка при записи конца файла");
        return ;
    }

    png_write_end(m_png_ptr, NULL);

    png_destroy_write_struct(&m_png_ptr, &m_info_ptr);
    fclose(fp);
}


bool Image_PNG::wasInitialized(){
    if (m_path_to_img == ""){
        return false;
    }else {
        return true;
    }
}


void  Image_PNG::freeImage(){
    if (m_arr_pixel != NULL){
        for (int i = 0; i < m_height; i++)
            free(m_arr_pixel[i]);
        free(m_arr_pixel);
    }
    m_arr_pixel = NULL;
}


//Деструктор
Image_PNG::~Image_PNG() {
    freeImage();
}

//Конструктор
Image_PNG::Image_PNG() {    }


//вспомогательная фнкция для конструктора копирования и operator=
void Image_PNG::deepCopy(const Image_PNG &img){

    if (m_arr_pixel != NULL){
        freeImage();
    }

    if (img.m_arr_pixel == NULL){
        m_arr_pixel = NULL;
        return;
    } else {
        m_width = img.m_width;
        m_height = img.m_height;
        m_color_type = img.m_color_type;
        m_bit_depth = img.m_bit_depth;
        m_path_to_img = img.m_path_to_img;

        m_arr_pixel = (png_bytep *) malloc(sizeof(png_bytep) * m_height);
        for (int i = 0; i < m_height; i++)
            m_arr_pixel[i] = (png_byte *) malloc(sizeof(png_byte) * m_width * 4);// так как канолов 4


        for (int y = 0; y < m_height; y++) {
            for (int x = 0; x < (m_width*4); x++) {//4 - количество каналов (в RGBA их 4)
                m_arr_pixel[y][x] = img.m_arr_pixel[y][x];
            }
        }
    }

}


//Конструктор копирования
Image_PNG::Image_PNG(const Image_PNG &img) {
    deepCopy(img);
}


Image_PNG& Image_PNG::operator=(const Image_PNG &img){

    if (this != &img){//проверка на самоприсвоение(тк мы очищаем память в deepCopy)
        deepCopy(img);
    }

    return *this;
}


//запись на диск по умл.(в файл с которого было считано)
void Image_PNG::writeOnDisk() {
    Image_PNG::writeOnDisk(m_path_to_img);
}


//чтение изображения с диска
int Image_PNG::readFromDisk( QString path){
    char header[SIZE_BIT_CHECK_PNG];    // 8 is the maximum size that can be checked

    std::string tmp_str =   path.toStdString();
    const char *c_path = tmp_str.c_str();

    /* open file and test for it being a png */
    FILE *fp = fopen(c_path, "rb");
    if (fp == NULL){
        // Some error handling: file could not be opened
        QMessageBox::critical(nullptr,"Ошибка","Файл с таким именем не найден");
        return 1;
    }

    fread(header,sizeof (header[0]), SIZE_BIT_CHECK_PNG, fp);//считывает массив эл из файла
    if (png_sig_cmp((png_const_bytep)header, 0, SIZE_BIT_CHECK_PNG)){//проверка что файл это png
        fclose(fp);
        // Some error handling: file is not recognized as a PNG

        QMessageBox::critical(nullptr,"Ошибка","Этот файл не PNG\n\nДанная прогрмма потдерживает только файлы формата *.png, с типом цвета RGBA");
        return 1;
    }


    /* выделение памяти для структур */
    m_png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (m_png_ptr == NULL){
        fclose(fp);
        // Some error handling: png_create_read_struct failed
        QMessageBox::critical(nullptr,"Ошибка","Не удалось выделить дин. память для структуры png_ptr");
        return 1;
    }

    m_info_ptr = png_create_info_struct(m_png_ptr);
    if (m_info_ptr == NULL){
        png_destroy_read_struct(&m_png_ptr,NULL, NULL);//очистка массива
        fclose(fp);
        // Some error handling: png_create_info_struct failed

        QMessageBox::critical(nullptr,"Ошибка","Не удалось выделить дин. память для структуры info_ptr");
        return 1;
    }

    if (setjmp(png_jmpbuf(m_png_ptr))){//обработка ошибок
        png_destroy_read_struct(&m_png_ptr,&m_info_ptr, NULL);//очистка массива
        fclose(fp);
        // Some error handling: error during init_io

        QMessageBox::critical(nullptr,"Ошибка","Не удалось считать данные об изображении");
        return 1;
    }

    png_init_io(m_png_ptr, fp); //настройка функция ввода/вывода
    png_set_sig_bytes(m_png_ptr, 8); //сообщить библиотеке что первые 8 байт отстутствуют

    png_read_info(m_png_ptr, m_info_ptr);//cчитывание файла с изб. в структуру

    //проверяем что файл png RGBA
    if (png_get_color_type(m_png_ptr, m_info_ptr) != PNG_COLOR_TYPE_RGB_ALPHA){
        png_destroy_read_struct(&m_png_ptr, &m_info_ptr, NULL);//очистка структуры
        fclose(fp);

        QMessageBox::critical(nullptr,"Ошибка","У этого png файла тип цвета не RGBA\n\nДанная программа работает только с файлами png  , с типом цвета  RGBA!!!");
        return 1;
    }

    //очищаем память от прошлого изображения(если оно было)
    freeImage();


    m_width = png_get_image_width(m_png_ptr, m_info_ptr);
    m_height = png_get_image_height(m_png_ptr, m_info_ptr);
    m_color_type = png_get_color_type(m_png_ptr, m_info_ptr);
    m_bit_depth = png_get_bit_depth(m_png_ptr, m_info_ptr);

    m_number_of_passes = png_set_interlace_handling(m_png_ptr);
    png_read_update_info(m_png_ptr, m_info_ptr);



    /* read file */
    if (setjmp(png_jmpbuf(m_png_ptr))){
        png_destroy_read_struct(&m_png_ptr, &m_info_ptr, NULL);//очистка структуры
        fclose(fp);
        // Some error handling: error during read_image

        QMessageBox::critical(nullptr,"Ошибка","Не удалось считать само  изображение");
        return 1;
    }


    // выделение памяти
    m_arr_pixel = (png_bytep *) malloc(sizeof(png_bytep) * m_height);
    for (int i = 0; i < m_height; i++)
        m_arr_pixel[i] = (png_byte *) malloc(png_get_rowbytes(m_png_ptr, m_info_ptr));

    // наконец считывание изображения
    png_read_image(m_png_ptr, m_arr_pixel);

    png_destroy_read_struct(&m_png_ptr, &m_info_ptr, NULL);//очистка структуры
    fclose(fp);


    m_path_to_img = path;
    return 0;

}


//запись изображения на диск
void Image_PNG::writeOnDisk(QString path) {
    Image_PNG::writeTempImgOnDisk(path);
    m_path_to_img = path;

}


//установливает в vall значение заданного канала channel во всем изб.
void Image_PNG::filterRGBA (int value,RGBA channel){
    int x,y;

    for (y = 0; y < m_height; y++) {
        for (x = 0; x < m_width; x++) {//4 - количество каналов (в RGBA их 4)
            png_byte *pixel = &(m_arr_pixel[y][x*4]);
            pixel[channel] = value;
        }
    }
    //m_height+=100;

}

int Image_PNG::getHeight() {
    return this->m_height;
}

int Image_PNG::getWidth() {
    return this->m_width;
}


Image_PNG Image_PNG::getPieceImg(int p_x, int p_y, int width, int height){
    Image_PNG p_img;

    p_img.m_height = height;
    p_img.m_width = width;

    //выделяем память
    p_img.m_arr_pixel = (png_bytep *) malloc(sizeof(png_bytep) * p_img.m_height);
    for (int i = 0; i < p_img.m_height; i++)
        p_img.m_arr_pixel[i] = (png_byte *) malloc(sizeof(png_byte) * p_img.m_width * 4);// так как канолов 4

    p_img.m_color_type = m_color_type;
    p_img.m_bit_depth = m_bit_depth;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < (width*4); x++) {//4 - количество каналов (в RGBA их 4)
            p_img.m_arr_pixel[y][x] = m_arr_pixel[y+p_y][x+p_x*4];
        }
    }

    return p_img;

}


QVector<QVector<Image_PNG>> Image_PNG::cutIntoPieces(int N, int M){
    QVector<QVector<Image_PNG>> arr_pieces_img;
    int x,y;


    //выделяем память
    arr_pieces_img.resize(N);
    for (int x = 0; x < N ; x++){
          arr_pieces_img[x].resize(M);
    }

    /*борьба с не кратностью изображения на N и на M*/
    //cредняя длина и выстона  кусков
    int width_piece = m_width / N; //целочисленное деление
    int height_piece = m_height / M;

    //остатки
    int remainder_x = m_width % N;
    int remainder_y = m_height % M;

    //прирост x
    int inc_x  ;
    int inc_y ;

    //координаты текущего куска
    int coordinate_x = 0;
    int coordinate_y = 0;

    //разрезание
    inc_x = 1;
    for (x = 0; x < N; x++) {
        if (remainder_x == x) {//сколько оcтатков столько и изображений которые нужно изменить по x
            inc_x = 0;//убираем надбавку ширины
        }

        inc_y = 1;

        for ( y = 0; y < M ; y++){
             if (remainder_y == y) {//сколько оcтатков столько и изображений которые нужно изменить по y
                 inc_y = 0;//убираем надбавку высоты
             }

             arr_pieces_img[x][y] = getPieceImg(coordinate_x ,coordinate_y,width_piece + inc_x, height_piece + inc_y);
             coordinate_y += height_piece + inc_y;//ноыве коорд для след куска по y
        }
        coordinate_y = 0;

        coordinate_x += width_piece + inc_x;//ноыве коорд для след куска по x
    }



    return  arr_pieces_img;
}


//нарисовать окружность
void Image_PNG::drawCircle(int centr_x, int centr_y, int r, int d,   QColor color, QColor color_in) {
    int x,y;

    for (y = centr_y-r-d; y <= centr_y+r+d; y++) {//так как круг зажат в квадрате
        for (x = centr_x-r-d; x <= centr_x+r+d; x++) {//c коорд.  лев верх (centr_x-r-d,centr_y-r-d)
                                                  //и низ прав (centr_x+r+d,centr_y+r+d)

            int crcl_in = qPow(x-centr_x,2) +qPow(y-centr_y,2) - qPow(r,2);
            int crcl_out = qPow(x-centr_x,2) +qPow(y-centr_y,2) - qPow(r+d,2);

            if (  crcl_in >= 0 && crcl_out < 0 ){
                setColorInPixel(x, y, color);
            }

        }
    }

    if (color_in.isValid()) {
        drawCircle(centr_x,centr_y,0,r,color_in);
    }

}


void Image_PNG::drawLine(int x1, int y1, int x2, int y2,int d , QColor color ) {
    int x,y;

    if (x1 == x2){ //вертикальная линия (tg равен inf)
        //уравнение вида x == const

        int inc_left = trunc((float)(d-1)/2);//окр в меньшую
        int inc_right = round((float)(d-1)/2);//окр в больщую

        set_first_small_second_big(&y1,&y2);
        for (y = y1; y <= y2; y++){
            for(x = x1 - inc_left; x <= x1+inc_right; x++){ //создание тольщины линии
               setColorInPixel(x, y, color);
            }
        }
        return;
    }

    float tg_a = (float)(y1 - y2)/(x1 - x2);
    float b = y1 - tg_a * x1;

    if (abs(tg_a) <= 1) {   //тогда строим y = y(x)
        set_first_small_second_big(&x1,&x2);

        int inc_up = trunc((float)(d-1)/2);//окр в меньшую
        int inc_down = round((float)(d-1)/2);//окр в больщую
        int y_main;

        for ( x = x1; x <= x2; x++) {
            y_main = round(tg_a*x + b);  // y = kx+b

            for(y = y_main - inc_up; y <= y_main+inc_down; y++){ //создание тольщины линии
                setColorInPixel(x, y, color);
            }
        }

    } else { //строим x = x(y)
        set_first_small_second_big(&y1,&y2);

        int inc_left = trunc((float)(d-1)/2);//окр в меньшую
        int inc_right = round((float)(d-1)/2);//окр в больщую
        int x_main;

        for ( y = y1; y <= y2; y++) {
            x_main = round( (y - b) / tg_a );  // x = (y-b)/k

            for(x = x_main - inc_left; x <= x_main+inc_right; x++){ //создание тольщины линии
                setColorInPixel(x, y, color);
            }
        }
    }
}


void Image_PNG::set_first_small_second_big(int *small_p, int *big_p){
    int small = *small_p;
    int big = *big_p;

    if (small > big) {//нужно наоборот
        *small_p = big;
        *big_p = small;
    }
}

void Image_PNG::setColorInPixel(int x, int y,QColor color) {
    png_byte *pixel;

    if (x >= 0 && x < m_width && y >= 0 && y < m_height){
        pixel = &(m_arr_pixel[y][x*4]);
        pixel[R] = color.red();
        pixel[G] = color.green();
        pixel[B] = color.blue();
        pixel[A] = color.alpha();
    }
}


void Image_PNG::drawRectangle(int x, int y,int width,int height,int d ,QColor color_out,  QColor color_in ){

    int inc_left = (d-1)/2;//окр в меньшую
    int inc_right = round((float)(d-1)/2);//окр в больщую
    int inc_up = inc_left;//окр в меньшую
    int inc_down = inc_right;//окр в больщую

    drawLine(x , y + inc_up, x + width-1, y + inc_up, d, color_out);    // up ---
    drawLine(x+width-inc_right-1, y+d, x+width-inc_right-1, y + height - d-1, d, color_out);    // right |
    drawLine(x, y+height-inc_down-1, x + width-1, y+height-inc_down-1, d, color_out);   // down ---
    drawLine(x+inc_left, y+d, x+inc_left, y + height - d-1, d, color_out);    // left |

    if (color_in.isValid()) {
        for(int i = x+d; i < x+width-d; i++) {
            for (int j = y+d; j < y+height-d;j++ ) {
                setColorInPixel(i,j,color_in);
            }
        }
    }
}

void Image_PNG::drawRectWithDiag(int x, int y,int width,int height,int d ,QColor color_out,  QColor color_in ) {
    drawRectangle(x,y,width,height,d,color_out,color_in);
    drawLine(x+d,y+d,x+width-d-1,y+height-d-1,d,color_out);
    drawLine(x+d,y+height-d-1,x+width-d-1,y+d,d,color_out);
}


