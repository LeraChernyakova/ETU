#ifndef DIALOGDRAWRECTWITHDIAG_H
#define DIALOGDRAWRECTWITHDIAG_H

#include <QDialog>

namespace Ui {
class DialogDrawRectWithDiag;
}

class DialogDrawRectWithDiag : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDrawRectWithDiag(QWidget *parent ,int &rect_x,int &rect_y,int &rect_width,int &rect_height,int &rect_d,bool &ok,QColor &color_in,QColor &color_out,int img_width,int img_height);
    ~DialogDrawRectWithDiag();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::DialogDrawRectWithDiag *ui;
    int &m_rect_x;
    int &m_rect_y;
    int &m_rect_width;
    int &m_rect_height;
    int &m_rect_d;
    bool &m_ok;
    QColor &m_color_in;
    QColor &m_color_out;
};

#endif // DIALOGDRAWRECTWITHDIAG_H
