#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <QMessageBox>
#include "dialog_drow_pramougolnik.h"
#include "dialog_ramka.h"
#include "dialog_split.h"
#include "sprawka.h"

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


void MainWindow::on_open_im_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл",
                                                    "/home",
                                                     "PNG_Images (*.png *.jpg)");
    if(fileName == ""){
        return;
    }

    if ( image.readFromDisk(fileName)){
        return;
    }

    viewImg();

}

void MainWindow::viewImg(){
    QString path = image.getPath();
    QPixmap view_img(path);
    ui->canvas->setFixedSize(view_img.size().width(),view_img.size().height());
    ui->canvas->setPixmap(view_img);
}



void MainWindow::on_Pramoygolnik_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }

    int x1, x2, y1, y2, h;
    QColor color_in, color_out;
    bool OK = 0;
    Dialog_Drow_Pramougolnik w_dialog_pramougolnic(nullptr, OK, x1, x2, y1, y2, h, color_out, color_in, image.getHeight(), image.getWidth());//получение данных прямоугольника
    w_dialog_pramougolnic.setModal(true);
    w_dialog_pramougolnic.exec();

    if (OK == false){
        return;
    }

    image.drawRectangle(x1, x2, y1, y2, h, color_out, color_in);

    image.writeOnDisk();

    viewImg();


}


void MainWindow::on_Ramka_1_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }

    int h;
    QColor color, color1;
    bool OK = 0;
    Dialog_Ramka w_dialog_ramka(nullptr, OK, h, color, color1);
    w_dialog_ramka.setModal(true);
    w_dialog_ramka.exec();

    if (OK == false){
        return;
    }

    int higth = image.getHeight(), width = image.getWidth();

    image.drawRectangle(0, width, 0, higth, h*2, color);
    image.drawRectangle(round(h*1.5)-0, width-round(h*1.5), round(h*1.5)-0, higth-round(h*1.5), round(h*1.5), color1);

    image.writeOnDisk();

    viewImg();

}


void MainWindow::on_Razdel_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }

    int n, m, d;
    QColor color;
    bool OK;
    int heigth = image.getHeight(), width = image.getWidth();
    Dialog_Split w_dialog_split(nullptr, OK, n, m, d, color, width, heigth);
    w_dialog_split.setModal(true);
    w_dialog_split.exec();

    if (OK == false){
        return;
    }

    image.drawLineNM(n, m, d, color);

    image.writeOnDisk();

    viewImg();
}


void MainWindow::on_Povorot_90_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }

    image.turnImage90();

    image.writeOnDisk();

    viewImg();

}


void MainWindow::on_Povorot_180_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }

    image.turnImage90();

    image.writeOnDisk();

    image.turnImage90();

    image.writeOnDisk();

    viewImg();
}


void MainWindow::on_Povorot_270_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }

    image.turnImage90();

    image.writeOnDisk();

    image.turnImage90();

    image.writeOnDisk();

    image.turnImage90();

    image.writeOnDisk();

    viewImg();
}


void MainWindow::on_Povorot_Rec_90_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }

    int x1, x2, y1, y2, h;
    QColor color_in, color_out;
    bool OK = 0;
    Dialog_Drow_Pramougolnik w_dialog_pramougolnic(nullptr, OK, x1, x2, y1, y2, h, color_out, color_in, image.getHeight(), image.getWidth());//получение данных прямоугольника
    w_dialog_pramougolnic.setModal(true);
    w_dialog_pramougolnic.exec();

    if (OK == false){
        return;
    }

    image.turnImagePis90(x1, y1, x2, y2);


    image.writeOnDisk();

    viewImg();
}


void MainWindow::on_Povorot_Rec_180_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }

    int x1, x2, y1, y2, h;
    QColor color_in, color_out;
    bool OK = 0;
    Dialog_Drow_Pramougolnik w_dialog_pramougolnic(nullptr, OK, x1, x2, y1, y2, h, color_out, color_in, image.getHeight(), image.getWidth());//получение данных прямоугольника
    w_dialog_pramougolnic.setModal(true);
    w_dialog_pramougolnic.exec();

    if (OK == false){
        return;
    }

    image.turnImagePis180(x1, y1, x2, y2);


    image.writeOnDisk();

    viewImg();
}


void MainWindow::on_Povorot_Rec_270_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }

    int x1, x2, y1, y2, h;
    QColor color_in, color_out;
    bool OK = 0;
    Dialog_Drow_Pramougolnik w_dialog_pramougolnic(nullptr, OK, x1, x2, y1, y2, h, color_out, color_in, image.getHeight(), image.getWidth());//получение данных прямоугольника
    w_dialog_pramougolnic.setModal(true);
    w_dialog_pramougolnic.exec();

    if (OK == false){
        return;
    }

    image.turnImagePis270(x1, y1, x2, y2);


    image.writeOnDisk();

    viewImg();
}


void MainWindow::on_action_triggered()
{
    Sprawka w_dialog_spr(nullptr);
    w_dialog_spr.setModal(true);
    w_dialog_spr.exec();
}

