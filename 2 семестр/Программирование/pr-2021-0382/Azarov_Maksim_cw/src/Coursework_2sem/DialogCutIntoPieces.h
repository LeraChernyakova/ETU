#ifndef DIALOGCUTINTOPIECES_H
#define DIALOGCUTINTOPIECES_H

#include <QDialog>

namespace Ui {
class DialogCutIntoPieces;
}

class DialogCutIntoPieces : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCutIntoPieces(QWidget *parent, int &N, int &M, QString &save_path,bool &ok, int img_width, int img_height);
    //N и M на сколько частей изб. разрезать по гориз. и вертик . соотв.
    //save_path куда сохрянить
    //ok действие было принято или отмененно
    //img_width и img_height ширина и высота изб. в пикс.

    ~DialogCutIntoPieces();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::DialogCutIntoPieces *ui;
    int &m_N;//на сколько частей нужно разрезать изб по горизонтали
    int &m_M;// по вертикали
    bool &m_ok;
    int m_img_height;
    int m_img_width;
    QString &m_save_path;//куда сохранить части
};

#endif // DIALOGCUTINTOPIECES_H
