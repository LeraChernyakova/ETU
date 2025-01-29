#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mandelbrot.h"
#include "mandelbrot_cl.h"

#include <chrono>

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , mandelbrot_{ nullptr }
    , calcType_{ 0 }
    , iterations_{ 255 }
    , width_{ 800 }
    , height_{ 600 }
{
    ui->setupUi(this);
    ui->comboBox->addItems( {
          "CPU serial"
        , "OpenCL parallel"
    } );
    ui->verticalLayout->setAlignment( Qt::AlignTop );
}


void MainWindow::recalc()
{
    if ( mandelbrot_ )
    {
        delete mandelbrot_;
    }

    if ( 0 == calcType_ )
    {
        mandelbrot_ = new Mandelbrot{ width_, height_, iterations_ };
    }
    else
    {
        mandelbrot_ = new MandelbrotCl{ width_, height_, iterations_ };
    }

    auto start = std::chrono::steady_clock::now();
    mandelbrot_->Generate();
    auto end = std::chrono::steady_clock::now();

    mandelbrot_->FillImage();
    ui->label->setPixmap( QPixmap::fromImage( mandelbrot_->Image() ) );

    size_t time = std::chrono::duration_cast< std::chrono::milliseconds >( ( end - start ) ).count();
    ui->label_2->setText( QString::fromStdString( std::to_string( time ) ) + " ms" );
}


MainWindow::~MainWindow()
{
    delete ui;
    delete mandelbrot_;
}


void MainWindow::on_comboBox_currentIndexChanged( int index )
{
    calcType_ = index;
    recalc();
}


void MainWindow::on_spinBox_valueChanged( int arg1 )
{
    iterations_ = arg1;
    recalc();
}


void MainWindow::on_spinBox_2_valueChanged( int arg1 )
{
    width_ = arg1;
    recalc();
}


void MainWindow::on_spinBox_3_valueChanged( int arg1 )
{
    height_ = arg1;
    recalc();
}

