#ifndef DIALOG_RAMKA_H
#define DIALOG_RAMKA_H

#include <QDialog>

namespace Ui {
class Dialog_Ramka;
}

class Dialog_Ramka : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Ramka(QWidget *parent, bool &OK, int &h, QColor &color, QColor &color1);
    ~Dialog_Ramka();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::Dialog_Ramka *ui;
    bool &ch_OK;
    int &ch_h;
    QColor &ch_color, &ch_color1;
};

#endif // DIALOG_RAMKA_H
