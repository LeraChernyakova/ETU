#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageviewer.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,
                       tr("Выберите изображения"), "", tr("Image Files (*.png)"));

    if (filepath.length()){
        ImageViewer* imgV = new ImageViewer;
        imgV->show();
        imgV->setAttribute(Qt::WA_DeleteOnClose);
        imgV->init();
        imgV->setFile(filepath);
        imgV->start();
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString info = "Вас приветствует программа обработки изображений!\n \
    Данная программа позволяет обрабатывать файлы типа PNG c форматом пикселей RGB.\n \
    Программа имеет следующие функции:\n \
    >> Скопировать заданную область \n \
    >> Заменить все пиксели одного цвета на другой \n \
    >> Сделать рамку\n \
    >> Найти все прямоугольники заданного цвета";

    QMessageBox::information(this, "Справка", info);
}

