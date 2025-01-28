#ifndef DIALOG_SPLIT_H
#define DIALOG_SPLIT_H

#include <QDialog>

namespace Ui {
class Dialog_Split;
}

class Dialog_Split : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Split(QWidget *parent, bool &OK, int &n, int &m, int &d, QColor &color, int max_x, int max_y);
    ~Dialog_Split();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::Dialog_Split *ui;
    bool &ch_OK;
    int &ch_n, &ch_m, &ch_d, ch_max_x, ch_max_y;
    QColor &ch_color;
};

#endif // DIALOG_SPLIT_H
