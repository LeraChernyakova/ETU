#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->verticalLayout->setAlignment(Qt::AlignTop);

    disconnect(ui->typeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_typeComboBox_currentIndexChanged);

    ui->typeComboBox->addItem("Hyperboloid");
    ui->typeComboBox->addItem("Cylinder");
    ui->typeComboBox->addItem("Torus");
    ui->typeComboBox->setCurrentIndex(0);

    connect(ui->typeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_typeComboBox_currentIndexChanged);

    connect(ui->rotOxSlider, &QSlider::valueChanged, this, &MainWindow::updateRotation);
    connect(ui->rotOySlider, &QSlider::valueChanged, this, &MainWindow::updateRotation);
    connect(ui->rotOzSlider, &QSlider::valueChanged, this, &MainWindow::updateRotation);

    connect(ui->scaleOxSlider, &QSlider::valueChanged, this, &MainWindow::updateScale);
    connect(ui->scaleOySlider, &QSlider::valueChanged, this, &MainWindow::updateScale);
    connect(ui->scaleOzSlider, &QSlider::valueChanged, this, &MainWindow::updateScale);

    connect(ui->transOxSlider, &QSlider::valueChanged, this, &MainWindow::updateTranslation);
    connect(ui->transOySlider, &QSlider::valueChanged, this, &MainWindow::updateTranslation);
    connect(ui->transOzSlider, &QSlider::valueChanged, this, &MainWindow::updateTranslation);


}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::updateRotation() {
    ui->glWindow->setRotation(
        ui->rotOxSlider->value(),
        ui->rotOySlider->value(),
        ui->rotOzSlider->value()
    );
}


void MainWindow::updateScale() {
    ui->glWindow->setScale(
        ui->scaleOxSlider->value() / 50.f,
        ui->scaleOySlider->value() / 50.f,
        ui->scaleOzSlider->value() / 50.f
    );
}


void MainWindow::updateTranslation() {
    ui->glWindow->setTranslation(
        ui->transOxSlider->value() / 100.f,
        ui->transOySlider->value() / 100.f,
        ui->transOzSlider->value() / 100.f
    );
}


void MainWindow::on_fragFactorBox_valueChanged(int arg1) {
    ui->glWindow->setFragmentationFactor(arg1);
}

void MainWindow::on_typeComboBox_currentIndexChanged(int index) {
    QString selectedText = ui->typeComboBox->itemText(index);
    std::string str = selectedText.toStdString();
    ui->glWindow->setType(str);
}

