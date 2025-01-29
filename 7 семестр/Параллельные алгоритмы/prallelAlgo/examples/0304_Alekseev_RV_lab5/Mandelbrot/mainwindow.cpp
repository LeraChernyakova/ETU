#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <chrono>
#include <mandelbrot.h>
#include <mandelbrot_cl.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mandelbrot_{nullptr}
    , calcType_{0}
    , iterations_{100}
    , width_{800}
    , height_{600}
{
    ui->setupUi(this);
    ui->comboBox_3->addItems({
                                 "CPU",
                                 "OpenCL"
                             });
    ui->verticalLayout_3->setAlignment(Qt::AlignTop);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mandelbrot_;
}


void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    calcType_ = index;
    recalc();
}


void MainWindow::on_spinBox_7_valueChanged(int arg1)
{
    iterations_ = arg1;
    recalc();
}


void MainWindow::on_spinBox_8_valueChanged(int arg1)
{
    width_ = arg1;
    recalc();
}


void MainWindow::on_spinBox_9_valueChanged(int arg1)
{
    height_ = arg1;
    recalc();
}

void MainWindow::recalc()
{
    if (mandelbrot_) {
        delete mandelbrot_;
    }

    if (calcType_ == 0) {
        mandelbrot_ = new Mandelbrot{width_, height_, iterations_};
    } else {
        mandelbrot_ = new Mandelbrot_CL{width_, height_, iterations_};
    }

    auto start = std::chrono::steady_clock::now();
    mandelbrot_->Generate();
    auto end = std::chrono::steady_clock::now();

    mandelbrot_->FillImage();
    ui->label_13->setPixmap(QPixmap::fromImage(mandelbrot_->Image()));

    size_t time = std::chrono::duration_cast<std::chrono::milliseconds>((end - start)).count();
    ui->label_18->setText(QString::fromStdString(std::to_string(time)) + " мс");
}

