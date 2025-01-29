#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Mandelbrot;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged( int index );
    void on_spinBox_valueChanged( int arg1 );
    void on_spinBox_2_valueChanged( int arg1 );
    void on_spinBox_3_valueChanged( int arg1 );

private:
    void recalc();

    Ui::MainWindow *ui;
    Mandelbrot* mandelbrot_;
    size_t calcType_;
    size_t iterations_;
    size_t width_;
    size_t height_;
};
#endif // MAINWINDOW_H
