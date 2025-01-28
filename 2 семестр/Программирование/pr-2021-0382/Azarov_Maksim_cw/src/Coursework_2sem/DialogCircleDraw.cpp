#include "DialogCircleDraw.h"
#include "ui_dialog_circle_draw.h"
#include <QString>
#include <QMessageBox>
#include <QColorDialog>

DialogCircleDraw::DialogCircleDraw(QWidget *parent,int &x,int &y,int &r,int &d,bool &ok,QColor &color_in,QColor &color_out,int img_width,int img_height) :
    QDialog(parent),
    ui(new Ui::DialogCircleDraw), m_x(x), m_y(y), m_r(r), m_d(d), m_ok(ok), m_color_in(color_in), m_color_out(color_out)
{
    ui->setupUi(this);
    m_ok = false;
    m_img_width = img_width;
    m_img_height = img_height;
    ui->label_X_info->setText("(Размер текущего изображения "+QString::number(img_width)+"(X) на "+QString::number(img_height)+"(Y))");
}

DialogCircleDraw::~DialogCircleDraw()
{
    delete ui;
}

void DialogCircleDraw::on_buttonBox_rejected()
{
    close();
}


void DialogCircleDraw::on_buttonBox_accepted()
{
    bool flag_ok_X, flag_ok_Y, flag_ok_R,flag_ok_d ;
    QString str_X = ui->line_X->text();
    QString str_Y = ui->line_Y->text();
    QString str_R = ui->line_R->text();
    QString str_d = ui->line_d->text();

    if (str_X == "" || str_Y == "" || str_R == "" || str_d == ""){
        QMessageBox::warning(nullptr,"Oшибка","Вы не ввели все значения");
        return;
    }

    int X = str_X.toInt(&flag_ok_X);
    int Y = str_Y.toInt(&flag_ok_Y);
    int R = str_R.toInt(&flag_ok_R);
    int d = str_d.toInt(&flag_ok_d);


    if (flag_ok_X == false || flag_ok_Y == false || flag_ok_R == false || flag_ok_d == false ){
        QMessageBox::warning(nullptr,"Oшибка","Ведите значения полей целлым числом");
        return;
    }

    if (R < 0 || d < 0){
        QMessageBox::warning(nullptr,"Oшибка","Значения радиуса и толщины должны быть неотрицательными");
        return;
    }

    QColor color_out = QColorDialog::getColor(Qt::red,nullptr,"Выберите цвет окружности",QColorDialog::ShowAlphaChannel);
    QColor color_in;//изначально color не Valid

    if ( !color_out.isValid() ){
      return;
    }


    if (ui->radioButton->isChecked()) {
        color_in = QColorDialog::getColor(Qt::red,nullptr,"Выберите цвет заливки окружности",QColorDialog::ShowAlphaChannel);
        if ( !color_in.isValid() ){
          return;
        }
    }

    m_x = X;
    m_y = Y;
    m_r = R;
    m_d = d;
    m_color_in = color_in;
    m_color_out = color_out;

    m_ok = true;
    close();
}

