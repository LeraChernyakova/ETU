#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "images.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void viewImg();
    ~MainWindow();

private slots:
    void on_open_im_triggered();

    void on_Pramoygolnik_triggered();

    void on_Ramka_1_triggered();

    void on_Razdel_triggered();

    void on_Povorot_Rec_180_triggered();

    void on_Povorot_90_triggered();

    void on_Povorot_Rec_90_triggered();

    void on_Povorot_180_triggered();

    void on_Povorot_270_triggered();

    void on_Povorot_Rec_270_triggered();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    Images image;
};
#endif // MAINWINDOW_H
