#ifndef DIALOG_DROW_PRAMOUGOLNIK_H
#define DIALOG_DROW_PRAMOUGOLNIK_H

#include <QDialog>

namespace Ui {
class Dialog_Drow_Pramougolnik;
}

class Dialog_Drow_Pramougolnik : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Drow_Pramougolnik(QWidget *parent, bool &OK, int &x1, int &x2, int &y1, int &y2, int &h, QColor &color_out, QColor &color_in, int higth, int width);
    ~Dialog_Drow_Pramougolnik();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::Dialog_Drow_Pramougolnik *ui;
    bool &ch_OK;
    int &ch_x1, &ch_x2, &ch_y1, &ch_y2, &ch_h;
    QColor &ch_color_out, &ch_color_in;
};

#endif // DIALOG_DROW_PRAMOUGOLNIK_H
