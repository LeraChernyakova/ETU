#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("Ярусова Татьяна, Чернякова Валерия КГ Лаб. 6");
    return a.exec();
}
