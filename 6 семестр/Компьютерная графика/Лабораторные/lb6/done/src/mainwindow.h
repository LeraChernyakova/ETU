#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/qopengl.h>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private slots:
    void on_fragFactorBox_valueChanged(int arg1);
    void on_typeComboBox_currentIndexChanged(int index);

private:
    void updateRotation();
    void updateScale();
    void updateTranslation();

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
