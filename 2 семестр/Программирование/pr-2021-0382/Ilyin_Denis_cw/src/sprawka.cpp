#include "sprawka.h"
#include "ui_sprawka.h"

Sprawka::Sprawka(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sprawka)
{
    ui->setupUi(this);
}

Sprawka::~Sprawka()
{
    delete ui;
}
