#ifndef SPRAWKA_H
#define SPRAWKA_H

#include <QDialog>

namespace Ui {
class Sprawka;
}

class Sprawka : public QDialog
{
    Q_OBJECT

public:
    explicit Sprawka(QWidget *parent = nullptr);
    ~Sprawka();

private:
    Ui::Sprawka *ui;
};

#endif // SPRAWKA_H
