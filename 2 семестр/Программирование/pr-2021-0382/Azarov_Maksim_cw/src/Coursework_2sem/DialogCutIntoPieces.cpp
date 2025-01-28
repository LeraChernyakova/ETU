#include "DialogCutIntoPieces.h"
#include "ui_w_cut_into_pieces.h"
#include <QMessageBox>
#include <QFileDialog>

DialogCutIntoPieces::DialogCutIntoPieces(QWidget *parent, int &N, int &M, QString &save_path, bool &ok, int img_width, int img_height) :
    QDialog(parent),
    ui(new Ui::DialogCutIntoPieces), m_N(N), m_M(M), m_save_path(save_path), m_ok(ok)
{
    ui->setupUi(this);
    m_ok = false;
    m_img_height = img_height;
    m_img_width = img_width;
    ui->label_N_info->setScaledContents(true);
    ui->label_N_info->setText("(от 1 до "+QString::number(m_img_width)+")");
    ui->label_M_info->setText("(от 1 до "+QString::number(img_height)+")");
}

DialogCutIntoPieces::~DialogCutIntoPieces()
{
    delete ui;
}

void DialogCutIntoPieces::on_buttonBox_rejected()
{
    close();
}


void DialogCutIntoPieces::on_buttonBox_accepted()
{
    bool flag_ok_N, flag_ok_M;
    QString str_N = ui->lineEdit_N->text();
    QString str_M = ui->lineEdit_M->text();

    if ((str_N == "") || (str_M == "")){
        QMessageBox::warning(nullptr,"Oшибка","Вы не ввели значения");
        return;
    }

    int N = str_N.toInt(&flag_ok_N);
    int M = str_M.toInt(&flag_ok_M);


    if ((flag_ok_N == false)||(flag_ok_M == false)||(N > m_img_width)||(N < 1)||(M > m_img_height)||(M < 1)){
        QMessageBox::warning(nullptr,"Oшибка","Ведите значения полей числом , по горизонтали в пределах 1 - "+
                             QString::number(m_img_width)+", а по вертикали 1 - "+QString::number(m_img_height));
        return;
    }

    //QString dir = QFileDialog::getExistingDirectory(this, tr("Сохранить в "),
                                                   // "/home",
                                                   // QFileDialog::ShowDirsOnly);

    QString current_name = "piece.png";
    QString current_path = "/home";
    QString fileName = QFileDialog::getSaveFileName(this, "Cохранить в",
                                                    current_path+"/"+current_name);
    if (fileName == ""){
        return;
    }

    m_M = M;
    m_N = N;
    m_save_path = fileName;

    m_ok = true;
    close();
}

