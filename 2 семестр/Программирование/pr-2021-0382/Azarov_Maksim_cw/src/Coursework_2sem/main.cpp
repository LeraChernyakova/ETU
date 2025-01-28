#include "mainwindow.h"
#include <QApplication>
#include "Image_PNG.h"
#include <QMessageBox>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window;
    window.setWindowIcon(QIcon(":/res/Image/icon_2.png"));

    //window.setGeometry(500,250,1000,500);


    window.show();
    QMessageBox::warning(&window,"Внимание","Данная прогрмма в стадии разработки , и потдерживает только файлы формата *.png, с типом цвета RGBA");

    return a.exec();
}
