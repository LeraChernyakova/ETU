#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Image_PNG.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void viewImg(const QString path);//отобразить изб

private slots:

    void on_act_open_file_triggered();

    void on_save_in_new_file_triggered();

    void on_rgba_filter_triggered();

    void on_save_In_same_file_triggered();

    void on_cutIntoPieces_triggered();

    void on_draw_circle_triggered();

    void on_draw_square_triggered();

    void resize_canvas();

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    Ui::MainWindow *ui;
    Image_PNG image;
    QString m_path_temp_img = "";
    int m_width_canvas;
    int m_height_canvas;

};
#endif // MAINWINDOW_H
