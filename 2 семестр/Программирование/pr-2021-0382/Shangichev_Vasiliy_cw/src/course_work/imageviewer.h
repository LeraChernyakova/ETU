#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H
#include "png_structs.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include "dialog.h"
#include "read_write_functions.h"
#include "pixel_functions.h"
#include "get_ornament.h"
#include "search_rectangles.h"
#include "copy_frame.h"

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = nullptr);
    ~ImageViewer();
    void start();
    void setFile(QString filepath){
        filename = filepath;
    }

    void init(){
        scene = new QGraphicsScene(this);
        png_file = new struct Png;
    }



private slots:
    void set_ornament();
    void refresh();
    void on_actionsearch_rectangles_triggered();
    int get_color(png_byte color[], QString info);
    void on_actionchange_color_triggered();
    void on_actioncopy_frame_triggered();
    int valid(struct FrameCopy* fcopy);

private:
    Ui::ImageViewer *ui;
    QGraphicsScene* scene;
    QPixmap image;
    struct Png* png_file;
    QString filename;
};

#endif // IMAGEVIEWER_H






