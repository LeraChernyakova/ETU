#include "dialog_ramka.h"
#include "ui_dialog_ramka.h"
#include <QMessageBox>
#include <QColorDialog>

Dialog_Ramka::Dialog_Ramka(QWidget *parent, bool &OK, int &h, QColor &color, QColor &color1) :
    QDialog(parent),
    ui(new Ui::Dialog_Ramka), ch_OK(OK), ch_h(h), ch_color(color), ch_color1(color1)
{
    ui->setupUi(this);
}

Dialog_Ramka::~Dialog_Ramka()
{
    delete ui;
}

void Dialog_Ramka::on_buttonBox_rejected()
{
    close();
}


void Dialog_Ramka::on_buttonBox_accepted()
{
    bool flag_ok_h;
    QString str_h = ui->lineEdit->text();

    if (str_h == ""){
        QMessageBox::warning(nullptr,"Oшибка","Вы не ввели значение");
        return;
    }

    int h = str_h.toInt(&flag_ok_h);

    if (flag_ok_h == false ){
        QMessageBox::warning(nullptr,"Oшибка","Ведите значения полей целыми числами");
        return;
    }

    if (h < 0){
        QMessageBox::warning(nullptr,"Oшибка","Значения толщины должно быть неотрицательным");
        return;
    }

    QColor color = QColorDialog::getColor(Qt::red,nullptr,"Выберите цвет внешней рамки",QColorDialog::ShowAlphaChannel);
    QColor color1;//изначально color не Valid

    if ( !color.isValid() ){
      return;
    }


    if (ui->radioButton->isChecked()) {
        color1 = QColorDialog::getColor(Qt::red,nullptr,"Выберите цвет внутренней рамки",QColorDialog::ShowAlphaChannel);
        if ( !color1.isValid() ){
          return;
        }
    }


    ch_h = h;
    ch_color = color;
    ch_color1 = color1;

    ch_OK = true;
    close();

}

