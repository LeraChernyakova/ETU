#include "DialogDrawRectWithDiag.h"
#include "ui_dialog_draw_rect_with_diag.h"
#include <QMessageBox>
#include <QColorDialog>

DialogDrawRectWithDiag::DialogDrawRectWithDiag(QWidget *parent , int &rect_x, int &rect_y, int &rect_width,
                                               int &rect_height, int &rect_d, bool &ok,QColor &color_in,
                                               QColor &color_out, int img_width, int img_height) :
    QDialog(parent),
    ui(new Ui::DialogDrawRectWithDiag),m_rect_x(rect_x),m_rect_y(rect_y),
    m_rect_width(rect_width),m_rect_height(rect_height),m_rect_d(rect_d),
    m_ok(ok),m_color_in(color_in),m_color_out(color_out)
{
    ui->setupUi(this);
    m_ok = false;
    ui->label_X_info->setText("(Размер текущего изображения "+QString::number(img_width)+"(X) на "+QString::number(img_height)+"(Y))");
}

DialogDrawRectWithDiag::~DialogDrawRectWithDiag()
{
    delete ui;
}

void DialogDrawRectWithDiag::on_buttonBox_rejected()
{
    close();
}


void DialogDrawRectWithDiag::on_buttonBox_accepted()
{
    bool flag_ok_X, flag_ok_Y, flag_ok_height,flag_ok_width, flag_ok_d;
    QString str_X = ui->line_X->text();
    QString str_Y = ui->line_Y->text();
    QString str_height = ui->line_height->text();
    QString str_width = ui->line_width->text();
    QString str_d = ui->line_d->text();


    if (str_X == "" || str_Y == "" || str_height == "" || str_width == "" || str_d == ""){
        QMessageBox::warning(nullptr,"Oшибка","Вы не ввели все значения");
        return;
    }

    int X = str_X.toInt(&flag_ok_X);
    int Y = str_Y.toInt(&flag_ok_Y);
    int width = str_width.toInt(&flag_ok_width);
    int height = str_height.toInt(&flag_ok_height);
    int d = str_d.toInt(&flag_ok_d);


    if (flag_ok_X == false || flag_ok_Y == false || flag_ok_height == false ||  flag_ok_width == false || flag_ok_d == false ){
        QMessageBox::warning(nullptr,"Oшибка","Ведите значения полей целлым числом от  -2*10^9 до 2*10^9");//надо проверить влезает число в int
        return;
    }

    if (height < 0 || width < 0 || d < 0){
        QMessageBox::warning(nullptr,"Oшибка","Значения размеров прямоугольника и толщины линии должны быть неотрицательными");
        return;
    }

    QColor color_out = QColorDialog::getColor(Qt::red,nullptr,"Выберите цвет линий прямоугольника",QColorDialog::ShowAlphaChannel);
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

    m_rect_x = X;
    m_rect_y = Y;
    m_rect_height = height;
    m_rect_width = width;
    m_rect_d = d;
    m_color_in = color_in;
    m_color_out = color_out;

    m_ok = true;
    close();
}

