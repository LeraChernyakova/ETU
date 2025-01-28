#ifndef DIALOGCIRCLEDRAW_H
#define DIALOGCIRCLEDRAW_H

#include <QDialog>
#include "Image_PNG.h"

namespace Ui {
class DialogCircleDraw;
}

class DialogCircleDraw : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCircleDraw(QWidget *parent ,int &x,int &y,int &r,int &d,bool &ok,QColor &color_in,QColor &color_out,int img_width,int img_height);
    ~DialogCircleDraw();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::DialogCircleDraw *ui;
    int &m_x;
    int &m_y;
    int &m_r;
    int &m_d;
    bool &m_ok;
    int m_img_width;
    int m_img_height;
    QColor &m_color_in;
    QColor &m_color_out;
};

#endif // DIALOGCIRCLEDRAW_H
