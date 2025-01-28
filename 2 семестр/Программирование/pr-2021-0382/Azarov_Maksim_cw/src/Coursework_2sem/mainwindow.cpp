#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "Image_PNG.h"
#include <QMessageBox>
#include <window_rgba_filter.h>
#include <QSplitter>
#include <QString>
#include "DialogCutIntoPieces.h"
#include "DialogCircleDraw.h"
#include <array>
#include "DialogDrawRectWithDiag.h"
#include <QWheelEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->setIconSize(QSize(40, 40));

    //connect(ui->canvas,&QWheelEvent::angleDelta,this,&MainWindow::resize_canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (m_path_temp_img != ""){
        QFile::remove(m_path_temp_img);
    }
}

void MainWindow::resize_canvas(){
    close();
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if (image.wasInitialized() == true){
       int delta =  event->angleDelta().y()/5;
       if (m_height_canvas + delta >= 0 && m_width_canvas + delta>= 0){
           float ratio = (float)m_width_canvas / m_height_canvas;
           m_height_canvas += delta;
           m_width_canvas = (int)(ratio * m_height_canvas);
       }

       viewImg(m_path_temp_img);
    }


}

void MainWindow::on_act_open_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл",
                                                    "/home",
                                                     "PNG_Images (*.png *.jpg)");
    if (fileName == ""){
        return ;
    }

    //удаление предыдушего временного файла(если он есть)
    if (m_path_temp_img != ""){
        QFile::remove(m_path_temp_img);
    }

    //считываем изображение
    if ( image.readFromDisk(fileName)){
        return;
    }

    //создание временого файла в котором будут проходить изменения
    QString cur_dir = fileName;
    int i = cur_dir.length()-1;

    while ( cur_dir[i] != '/'){
        cur_dir.remove(i,1);
        i--;
    }
    m_path_temp_img = cur_dir+".temp";
    image.writeTempImgOnDisk(m_path_temp_img);

    m_height_canvas = image.getHeight();
    m_width_canvas = image.getWidth();

    //отображение в приложении
    viewImg(m_path_temp_img);
}

void MainWindow::viewImg(const QString path){
    QPixmap view_img(path);
    //ui->canvas->setFixedSize(view_img.size().width(),view_img.size().height());
    ui->canvas->setFixedSize(m_width_canvas, m_height_canvas);
    ui->canvas->setPixmap(view_img);
}


void MainWindow::on_save_in_new_file_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }
    QString current_name = "res.png";
    QString current_path = "/home";
    QString fileName = QFileDialog::getSaveFileName(this, "Cохранить файл",
                                                    current_path+"/"+current_name);
    if (fileName == ""){
        return ;
    }

    image.writeOnDisk(fileName);
}


void MainWindow::on_rgba_filter_triggered()
{

   if (image.wasInitialized() == false){
       QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
       return;
   }

   int val_chanl;
   RGBA chanl;
   bool ok;

   //запуск соотв. диалог. окна
   window_rgba_filter w_rgba_filter(nullptr,val_chanl,chanl,ok);//это экземпляр класса window_rgba_filter (да знаю криво назвал)
   w_rgba_filter.setModal(true);
   w_rgba_filter.exec();

   if (ok == false){
       return;
   }

   image.filterRGBA(val_chanl,chanl);
   image.writeTempImgOnDisk(m_path_temp_img);

   viewImg(m_path_temp_img);
}


void MainWindow::on_save_In_same_file_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Нечего сохранять" );
        return;
    }
    image.writeOnDisk();
}





void MainWindow::on_cutIntoPieces_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }

    int N,M;
    QString save_path;
    bool ok;

    DialogCutIntoPieces w_cut_into_pieces(nullptr, N, M, save_path,ok,image.getWidth(),image.getHeight());
    //доделать ok и save_path
    w_cut_into_pieces.setModal(true);
    w_cut_into_pieces.exec();//из-за этого виснет отладчик, почему интрсн???

    if (ok == false){
        return;
    }

    QVector<QVector <Image_PNG>>  arr_pieces_img;
    arr_pieces_img = image.cutIntoPieces(N, M);//N,M
    //проблемма в деструкторе Image_PNG//уже нет проблемы ))))но было сложно

    for (int y = 0; y < M; y++){
        for (int x = 0; x < N; x++){
            arr_pieces_img[x][y].writeOnDisk(save_path.remove(".png")+"("+QString::number(y+1)+";"+QString::number(x+1)+")"+".png");
        }
    }


}

void MainWindow::on_draw_circle_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }

    int x,y; //координаты центра
    int r,d;  //радиус и толщина
    bool ok;
    QColor color_in, color_out;

    DialogCircleDraw w_draw_circle(nullptr, x, y, r, d, ok,color_in,color_out,image.getWidth(),image.getHeight());
    w_draw_circle.setModal(true);
    w_draw_circle.exec();

    if (ok == false){
        return;
    }


    image.drawCircle(x, y, r, d, color_out, color_in);

    //перезапись временного файла
    image.writeTempImgOnDisk(m_path_temp_img);

    //отображение в приложении
    viewImg(m_path_temp_img);
}


void MainWindow::on_draw_square_triggered()
{
    if (image.wasInitialized() == false){
        QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали изображение" );
        return;
    }

    int x,width,y,height,d;
    QColor color_in,color_out;
    bool ok;

    DialogDrawRectWithDiag w_draw_rect(nullptr, x, y, width, height, d, ok,color_in,color_out,image.getWidth(),image.getHeight());
    w_draw_rect.setModal(true);
    w_draw_rect.exec();

    if (ok == false){
        return;
    }


    //color.setRed(255);
    //color_2.setGreen(255);
    //x = ui->lineEdit_X1->text().toInt();
    //width = ui->lineEdit_X2->text().toInt();
    //y = ui->lineEdit_Y1->text().toInt();
    //height = ui->lineEdit_Y2->text().toInt();
    //d = ui->lineEdit->text().toInt();

    image.drawRectWithDiag(x,y,width,height,d,color_out,color_in);

    //перезапись временного файла
    image.writeTempImgOnDisk(m_path_temp_img);

    //отображение в приложении
    viewImg(m_path_temp_img);

}

