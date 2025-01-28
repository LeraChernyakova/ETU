#include "dialog_split.h"
#include "ui_dialog_split.h"
#include <QMessageBox>
#include <QColorDialog>

Dialog_Split::Dialog_Split(QWidget *parent, bool &OK, int &n, int &m, int &d, QColor &color, int max_x, int max_y) :
    QDialog(parent),
    ui(new Ui::Dialog_Split), ch_OK(OK), ch_n(n), ch_m(m), ch_d(d), ch_color(color)
{
    ui->setupUi(this);
    ui->label_max_x->setText("Максимальное значение по горизонтали:   " + QString::number(max_x));
    ui->label_max_y->setText("Максимальное значение по вертикали:   " + QString::number(max_y));
    ch_max_x = max_x;
    ch_max_y = max_y;
}

Dialog_Split::~Dialog_Split()
{
    delete ui;
}

void Dialog_Split::on_buttonBox_rejected()
{
    close();
}


void Dialog_Split::on_buttonBox_accepted()
{
    bool flag_ok_n, flag_ok_m, flag_ok_d;
    QString str_n = ui->lineEdit_N->text();
    QString str_m = ui->lineEdit_M->text();
    QString str_d = ui->lineEdit_D->text();

    if (str_n == "" || str_m == "" || str_d == ""){
        QMessageBox::warning(nullptr,"Oшибка","Вы ввели не все значения");
        return;
    }

    int n = str_n.toInt(&flag_ok_n);
    int m = str_m.toInt(&flag_ok_m);
    int d = str_d.toInt(&flag_ok_d);

    if (flag_ok_n == false || flag_ok_m == false || flag_ok_d == false){
        QMessageBox::warning(nullptr,"Oшибка","Ведите значения полей целыми числами");
        return;
    }

    if (d < 0 || n < 1 || m < 1){
        QMessageBox::warning(nullptr,"Oшибка","Значения толщины должно быть неотрицательным, количество по горизонтали и по вертикали должно быть больше 0");
        return;
    }

    if (n > ch_max_x || m > ch_max_y){
        QMessageBox::warning(nullptr, "Ошибка", "Превышено максамально допустимое значениепо горизонтали и/или вертикали");
        return;
    }

    QColor color = QColorDialog::getColor(Qt::red,nullptr,"Выберите цвет полос",QColorDialog::ShowAlphaChannel);

    if ( !color.isValid() ){
      return;
    }

    ch_n = n;
    ch_m = m;
    ch_d = d;
    ch_color = color;

    ch_OK = true;
    close();
}

