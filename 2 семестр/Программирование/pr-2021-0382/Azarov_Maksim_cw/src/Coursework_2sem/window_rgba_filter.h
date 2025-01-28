#ifndef WINDOW_RGBA_FILTER_H
#define WINDOW_RGBA_FILTER_H

#include <QDialog>
#include "ui_window_rgba_filter.h"
#include "Image_PNG.h"

namespace Ui {
class window_rgba_filter;
}

class window_rgba_filter : public QDialog
{
    Q_OBJECT

public:
    explicit window_rgba_filter(QWidget *parent ,int &val_chanl,RGBA &chanl,bool &ok);
    ~window_rgba_filter();

private slots:



    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    int &m_val_chanl;
    RGBA &m_chanl;
    bool &m_ok;
    Ui::window_rgba_filter *ui;

};

#endif // WINDOW_RGBA_FILTER_H
