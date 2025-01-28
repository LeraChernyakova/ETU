#include "dialog_drow_pramougolnik.h"
#include "ui_dialog_drow_pramougolnik.h"
#include <QMessageBox>
#include <QColorDialog>


Dialog_Drow_Pramougolnik::Dialog_Drow_Pramougolnik(QWidget *parent, bool &OK, int &x1, int &x2, int &y1, int &y2, int &h, QColor &color_out, QColor &color_in, int higth, int width) :
    QDialog(parent),
    ui(new Ui::Dialog_Drow_Pramougolnik),ch_OK(OK), ch_x1(x1), ch_x2(x2), ch_y1(y1), ch_y2(y2), ch_h(h), ch_color_out(color_out), ch_color_in(color_in)
{
    ui->setupUi(this);
    ui->random->setText("Max x:   " + QString::number(width));
    ui->nerandom->setText("Max y:   " + QString::number(higth));
}

Dialog_Drow_Pramougolnik::~Dialog_Drow_Pramougolnik()
{
    delete ui;
}

void Dialog_Drow_Pramougolnik::on_buttonBox_rejected()
{
    close();
}


void Dialog_Drow_Pramougolnik::on_buttonBox_accepted()
{
    bool flag_ok_x1, flag_ok_x2, flag_ok_y1,flag_ok_y2,flag_ok_h;
    QString str_x1 = ui->lineEdit_x1->text();
    QString str_x2 = ui->lineEdit_x2->text();
    QString str_y1 = ui->lineEdit_y1->text();
    QString str_y2 = ui->lineEdit_y2->text();
    QString str_h = ui->lineEdit_h->text();

    if (str_x1 == "" || str_x2 == "" || str_y1 == "" || str_y2 == "" || str_h == ""){
        QMessageBox::warning(nullptr,"Oшибка","Вы ввели не все значения");
        return;
    }

    int x1 = str_x1.toInt(&flag_ok_x1);
    int x2 = str_x2.toInt(&flag_ok_x2);
    int y1 = str_y1.toInt(&flag_ok_y1);
    int y2 = str_y2.toInt(&flag_ok_y2);
    int h = str_h.toInt(&flag_ok_h);

    if (flag_ok_x1 == false || flag_ok_x2 == false || flag_ok_y1 == false || flag_ok_y2 == false || flag_ok_h == false ){
        QMessageBox::warning(nullptr,"Oшибка","Ведите значения полей целыми числами");
        return;
    }

    if (h < 0){
        QMessageBox::warning(nullptr,"Oшибка","Значения толщины должно быть неотрицательным");
        return;
    }

    QColor color_out = QColorDialog::getColor(Qt::red,nullptr,"Выберите цвет прямоугольника",QColorDialog::ShowAlphaChannel);
    QColor color_in;//изначально color не Valid

    if ( !color_out.isValid() ){
      return;
    }


    if (ui->radioButton->isChecked()) {
        color_in = QColorDialog::getColor(Qt::red,nullptr,"Выберите цвет заливки прямоугольника",QColorDialog::ShowAlphaChannel);
        if ( !color_in.isValid() ){
          return;
        }
    }

    ch_x1 = x1;
    ch_x2 = x2;
    ch_y1 = y1;
    ch_y2 = y2;
    ch_h = h;
    ch_color_in = color_in;
    ch_color_out = color_out;

    ch_OK = true;
    close();

}

