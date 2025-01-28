/* заголовочный файл класса Image_PNG.h */
/* интерфейс класса*/
/* работает только с RGBA*/

#ifndef IMAGE_PNG_H
#define IMAGE_PNG_H

#include <png.h>
#include <QString>
#include <QVector>
#include <QColor>

const int SIZE_BIT_CHECK_PNG = 8;

enum RGBA{//канал
    R, //=0
    G, //=1
    B, //=2
    A  //=3
};


/* объявление класса*/
class Image_PNG {
private:
    int m_width, m_height;//ширина и высота в изб. в пикселях
    png_byte **m_arr_pixel = NULL;//масив пикселей  изображение (трех мерный массив)
    png_byte m_color_type; //тип кодирования цвета (может быть только RGB)
    png_byte m_bit_depth;  //бит глубины
    QString m_path_to_img = "";// путь к изоб. (включая имя файла) // "" - означает что структура не инициализированна.

    png_structp m_png_ptr;
    png_infop m_info_ptr;
    int m_number_of_passes;

    void set_first_small_second_big(int *small_p, int *big_p);//в первую переменую устанавливает меньшее,
                                                             //во второую большее значение из переданых переменых
    void freeImage();   //вспомогательная фнкция для деструктора
    void deepCopy(const Image_PNG &img);    //вспомогательная фнкция для конструктора копирования и operator=
    void setColorInPixel(int x, int y,QColor color);  //если кординаты вне картинки ничего не делает
public:
    //Конструктор
    Image_PNG();

    ~Image_PNG();//деконструктор

    Image_PNG(const Image_PNG &img);//конструктор копирования

    Image_PNG& operator=(const Image_PNG &img);//и так понятно

    int readFromDisk(QString path); //считывание изб. с диска

    void writeOnDisk(QString path ); // записываем изб. на диск

    void writeOnDisk();//записываем изб. на диск по умл. от куда и было считано

    void writeTempImgOnDisk(QString temp_path );//записывает на диск временное изображение
    //отличается от writeOnDisk() тем что не изменяет m_path_to_img, то есть не превязывает екземпляр к новому файлу

    void filterRGBA (int value,RGBA channel);//устанавливает згачение value в канале channal во всех пикселях изб.

    bool wasInitialized(); //определяет была ли инициализирована структура

    int getHeight();//получить высоту изб. в пикс.

    int getWidth();//получить ширину в пикс.

    QVector<QVector<Image_PNG>> cutIntoPieces(int N, int M);// разрезать изображение на N*M частей

    Image_PNG getPieceImg(int x, int y, int width, int height); //получить один кусочек изображения
    //x и y координаты верхнего левого кусочка

    //рисует  окружность круг(вклюяая r , не включая r+d)// если color_in isValid() == true заливает внут. окружности
    void drawCircle(int centr_x, int centr_y, int r, int d, QColor color, QColor color_in = QColor::Invalid);

    //нарисовать отрезок
    void drawLine(int x1, int y1, int x2, int y2,int d , QColor color );

    //нарисовать прямоугольник //если color_in isValid то ресуется залитый
    void drawRectangle(int x, int y,int width,int height,int d ,QColor color_out,  QColor color_in = QColor::Invalid);

    //нарисовать примоугольник с диагоналями
    void drawRectWithDiag(int x, int y,int width,int height,int d ,QColor color_out,  QColor color_in = QColor::Invalid);



};

#endif // IMAGE_PNG_H
