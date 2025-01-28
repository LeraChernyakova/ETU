#include "imageviewer.h"
#include "ui_imageviewer.h"
#include <QDebug>
#define NUMCHANNELS 3

ImageViewer::ImageViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
    connect(ui->single_color, SIGNAL(triggered()), this, SLOT(set_ornament()));
    connect(ui->double_color, SIGNAL(triggered()), this, SLOT(set_ornament()));
}

ImageViewer::~ImageViewer()
{
    delete ui;
    delete png_file;
    delete scene;
}

int ImageViewer::valid(struct FrameCopy* fcopy){
    if (fcopy->left_top.x >= fcopy->right_bottom.x || fcopy->left_top.y >= fcopy->right_bottom.y){
        QMessageBox::critical(this, "Ошибка", "Левый верхний угол должен находится выше правого нижнего угла.");
        return 0;
    }
    return 1;
}

void ImageViewer::refresh(){
    write_png_file(png_file, filename);
    start();
}


void ImageViewer::start(){

    if (read_png_file(png_file, filename, this)){
        image.load(filename);
        int width = image.width();
        int height = image.height();
        ui->imgView->resize(width, height);
        ImageViewer::resize(width, height);
        scene->addPixmap(image);
        scene->setSceneRect(image.rect());
        ui->imgView->setScene(scene);
    } else {
        close();
    }
}

int ImageViewer::get_color(png_byte color[], QString info){
    QColor setting_color = QColorDialog::getColor(Qt::white, this, info);
    if (!setting_color.isValid()){
        return 0;
    }
    color[0] = setting_color.red();
    color[1] = setting_color.green();
    color[2] = setting_color.blue();
    return 1;
}

void ImageViewer::set_ornament()
{
    png_byte first_ornament_color[NUMCHANNELS];
    if (!get_color(first_ornament_color, "Выберите цвет")){
        return;
    }

    png_byte second_ornament_color[NUMCHANNELS];

    QAction* s = (QAction*)sender();
    if (s->text() == "два цвета"){
        if (!get_color(second_ornament_color, "Выберите второй цвет")){
            return;
        }
    } else {
        for (int i = 0; i < 2; i++){
            second_ornament_color[i] = first_ornament_color[i];
        }
    }

    int ornament_width = QInputDialog::getInt(this, "Выберите ширину рамки", "ширина", 0, 1);

    get_ornament(png_file, ornament_width, first_ornament_color, second_ornament_color);


    refresh();
}


void ImageViewer::on_actionsearch_rectangles_triggered()
{
    png_byte rec_color[NUMCHANNELS];
    if (!get_color(rec_color, "Выберите цвет прямоугольников")){
        return;
    }

    png_byte frame_color[NUMCHANNELS];
    if (!get_color(frame_color, "Выберите цвет обводки")){
        return;
    }

    int frame_width = QInputDialog::getInt(this, "Выберите ширину рамки", "ширина", 0, 1);
    find_rectangles(png_file, rec_color, frame_color, frame_width);

    refresh();
}


void ImageViewer::on_actionchange_color_triggered()
{
    png_byte replaced_color[NUMCHANNELS];
    png_byte color_for_replace[NUMCHANNELS];
    if (!get_color(replaced_color, "Выберите цвет, который надо заменить.")){
        return;
    }

    if (!get_color(color_for_replace, "Выберите цвет, на который будет заменен предыдущий.")){
        return;
    }
    change_color(png_file, replaced_color, color_for_replace);
    refresh();
}


void ImageViewer::on_actioncopy_frame_triggered()
{
    FrameCopy* fcopy = new FrameCopy;
    Dialog* new_window = new Dialog(png_file->width, png_file->height);
    int* was_closed = new int;
    new_window->setAttribute(Qt::WA_DeleteOnClose);
    new_window->set_frame(fcopy, was_closed);
    new_window->setModal(true);
    new_window->exec();
    if (!(*(was_closed))){
        // check valid
        if (valid(fcopy)){
            copy_frame(png_file, *fcopy);
            refresh();
        }
    }
    delete was_closed;
    delete fcopy;
}








