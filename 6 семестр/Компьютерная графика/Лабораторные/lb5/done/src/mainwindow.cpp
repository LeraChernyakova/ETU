#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("КГ. Лабораторная 5. Черянкова, Ярусова.");

    auto lightPos = [=]() {
        float x = ui->xSpinBox->value();
        float y = ui->ySpinBox->value();
        float z = ui->zSpinBox->value();
        ui->openGLWidget->changeLightPosition(QVector3D(x, y, z));
    };

    connect(ui->xSpinBox, &QDoubleSpinBox::valueChanged, ui->openGLWidget, lightPos);
    connect(ui->ySpinBox, &QDoubleSpinBox::valueChanged, ui->openGLWidget, lightPos);
    connect(ui->zSpinBox, &QDoubleSpinBox::valueChanged, ui->openGLWidget, lightPos);
}

MainWindow::~MainWindow()
{
    delete ui;
}

