#ifndef IMAGE_H
#define IMAGE_H

#include <png.h>
#include <QString>
#include <QVector>
#include <QColor>
#include <QString>

const int SIZE_BIT_CHECK_PNG = 8;

enum RGBA{//канал
    R, //=0
    G, //=1
    B, //=2
    A  //=3
};


/* объявление класса*/
class Images {
private:
    int m_width, m_height;//ширина и высота в изб. в пикселях
    png_byte **m_arr_pixel = NULL;//масив пикселей  изображение (трех мерный массив)
    png_byte m_color_type; //тип кодирования цвета (может быть только RGBA)
    png_byte m_bit_depth;  //бит глубины
    QString m_path_to_img = "";// путь к изоб. (включая имя файла) // "" - означает что структура не инициализированна.

    png_structp m_png_ptr; //по факту изначально само изображение
    png_infop m_info_ptr; //информация об изображении
    int m_number_of_passes;

    void set_first_small_second_big(int *small_p, int *big_p);//в первую переменую устанавливает меньшее,
                                                             //во второую большее значение из переданых переменых
    void freeImage();   //вспомогательная фнкция для деструктора
    void deepCopy(const Images &img);    //вспомогательная фнкция для конструктора копирования и operator=
    void setColorInPixel(int x, int y, QColor color);  //устанавливает в пиксель цвет //если кординаты вне картинки ничего не делает
    QColor getColorInPixel(int x, int y); //получает цвет из пикселя
public:
    //Конструктор
    Images();

    ~Images();//деконструктор

    int readFromDisk(QString path); //считывание изб. с диска

    bool wasInitialized(); //определяет была ли инициализирована структура

    int getHeight();//получить высоту изб. в пикс.

    int getWidth();//получить ширину в пикс.

    QString getPath();//получить потуть

    void writeOnDisk(); // записываем изб. на диск

    //нарисовать отрезок
    void drawLine(int x1, int y1, int x2, int y2,int d , QColor color);

    //нарисовать прямоугольник //если color_in isValid то ресуется залитый
    void drawRectangle(int x1, int x2,int y1,int y2,int d ,QColor color_out = QColor::Invalid,  QColor color_in = QColor::Invalid);

    //разделение изображения на части
    void drawLineNM(int n, int m, int d, QColor color);

    //поворот изображения
    void turnImagePis90(int x1, int y1, int x2, int y2);

    //поворот изображения
    void turnImagePis180(int x1, int y1, int x2, int y2);

    //поворот изображения
    void turnImagePis270(int x1, int y1, int x2, int y2);

    //поворот изображения
    void turnImage90();

    //поворот изображения
    void turnImage180();

};

#endif // IMAGE_H



























