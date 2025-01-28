#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(int width, int height, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->right_bottom_x->setValidator(new QIntValidator(0, width, this));
    ui->right_bottom_y->setValidator(new QIntValidator(0, height, this));
    ui->destination_x->setValidator(new QIntValidator(0, width, this));
    ui->destination_y->setValidator(new QIntValidator(0, height, this));
    ui->pushButton->setEnabled(false);

    ui->left_top_x->setValidator(new QIntValidator(0, width, this));
    ui->left_top_y->setValidator(new QIntValidator(0, height, this));

    connect(ui->left_top_x, SIGNAL(textChanged(QString)), this, SLOT(onTextchanged(QString)));
    connect(ui->left_top_y, SIGNAL(textChanged(QString)), this, SLOT(onTextchanged(QString)));
    connect(ui->right_bottom_x, SIGNAL(textChanged(QString)), this, SLOT(onTextchanged(QString)));
    connect(ui->right_bottom_y, SIGNAL(textChanged(QString)), this, SLOT(onTextchanged(QString)));
    connect(ui->destination_x, SIGNAL(textChanged(QString)), this, SLOT(onTextchanged(QString)));
    connect(ui->destination_y, SIGNAL(textChanged(QString)), this, SLOT(onTextchanged(QString)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::clean(QLineEdit* obj){
    QString cur = obj->text();
    if (cur.length() == 0){
        return;
    }
    if (cur.at(0) == '0'){
        obj->setText("0");
    }
}

int Dialog::check(){
   clean(ui->left_top_x);
   clean(ui->left_top_y);
   clean(ui->right_bottom_x);
   clean(ui->right_bottom_y);
   clean(ui->destination_x);
   clean(ui->destination_y);
   return !(ui->left_top_x->text().isEmpty() || ui->left_top_y->text().isEmpty() || \
            ui->right_bottom_x->text().isEmpty() || ui->right_bottom_y->text().isEmpty() || \
            ui->destination_x->text().isEmpty() || ui->destination_y->text().isEmpty());
}

void Dialog::onTextchanged(const QString &text){
    if (check()){
        ui->pushButton->setEnabled(true);
    }
}

void Dialog::on_pushButton_clicked()
{
    *(was_closed) = 0;
    frame_copy->left_top.x = ui->left_top_x->text().toInt();
    frame_copy->left_top.y = ui->left_top_y->text().toInt();
    frame_copy->right_bottom.x = ui->right_bottom_x->text().toInt();
    frame_copy->right_bottom.y = ui->right_bottom_y->text().toInt();
    frame_copy->destination.x = ui->destination_x->text().toInt();
    frame_copy->destination.y = ui->destination_y->text().toInt();
    close();
}
















