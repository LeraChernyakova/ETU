#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "png_structs.h"
#include <QLineEdit>
#include <QIntValidator>
#include <QDebug>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(int width, int height, QWidget *parent = nullptr);
    ~Dialog();
    void set_frame(FrameCopy* fcopy, int* wclosed){
        frame_copy = fcopy;
        was_closed = wclosed;
        *(was_closed) = 1;
    }

private slots:
    void on_pushButton_clicked();
    void onTextchanged(const QString & text);
    int check();
    void clean(QLineEdit* obj);

private:
    Ui::Dialog *ui;
    struct FrameCopy* frame_copy;
    int* was_closed;
};

#endif // DIALOG_H
