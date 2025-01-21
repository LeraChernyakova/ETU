#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/qopengl.h>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_lightTypeSelector_currentTextChanged(const QString &arg1);
    void on_positionX_valueChanged(double arg1);
    void on_positionY_valueChanged(double arg1);
    void on_positionZ_valueChanged(double arg1);
    void on_directionX_valueChanged(double arg1);
    void on_directionY_valueChanged(double arg1);
    void on_directionZ_valueChanged(double arg1);
    void on_cutoffSelector_valueChanged(double arg1);
    void on_outerCutoffSelector_valueChanged(double arg1);
    void on_lightAmbientSelector_clicked();
    void on_lightDiffuseSelector_clicked();
    void on_lightSpecularSelector_clicked();
    void on_shininessSelector_valueChanged(double arg1);
    void on_ambientStrengthSelector_valueChanged(double arg1);
    void on_figureSelector_valueChanged(int arg1);

    void on_materialDiffuseSelector_clicked();

    void on_materialSpecularSelector_clicked();

    void on_projectionSelector_currentTextChanged(const QString &arg1);

private:
    void init();
    void loadFigureMaterial();

    bool drag_ = false;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
