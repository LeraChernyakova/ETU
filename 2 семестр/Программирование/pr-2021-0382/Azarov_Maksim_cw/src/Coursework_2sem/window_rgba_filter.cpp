#include "window_rgba_filter.h"
#include "ui_window_rgba_filter.h"
#include <QMessageBox>

window_rgba_filter::window_rgba_filter(QWidget *parent,int &val_chanl,RGBA &chanl, bool &ok) :
    QDialog(parent),
    ui(new Ui::window_rgba_filter),m_val_chanl(val_chanl),m_chanl(chanl), m_ok(ok)
{
    ui->setupUi(this);
    m_ok = false;
}

window_rgba_filter::~window_rgba_filter()
{
    delete ui;
}



void window_rgba_filter::on_buttonBox_rejected()
{
    close();
}


void window_rgba_filter::on_buttonBox_accepted()
{
    bool flag_ok;
    QString s_val_chnl = ui->lineEdit->text();

    int val_chnl = s_val_chnl.toInt(&flag_ok);

    if ((flag_ok == false)||(val_chnl > 255)||(val_chnl < 0) ){
        QMessageBox::warning(nullptr,"Oшибка","Ведите значение числом от 0 до 255" );
        return;
    }

    if (ui->radioB_Red->isChecked()){
        m_val_chanl = val_chnl;
        m_chanl = R;

    }else if (ui->radioB_Green->isChecked()){
        m_val_chanl = val_chnl;
        m_chanl = G;

    }else if (ui->radioB_Blue->isChecked()){
        m_val_chanl = val_chnl;
        m_chanl = B;

    }else if (ui->radioB_Alpha->isChecked()){
        m_val_chanl = val_chnl;
        m_chanl = A;

    }else{
         QMessageBox::warning(nullptr,"Oшибка","Вы не выбрали канал" );
         return;
    }

    m_ok = true;
    close();

}

