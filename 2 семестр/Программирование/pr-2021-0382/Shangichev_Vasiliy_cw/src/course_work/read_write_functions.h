#ifndef READ_WRITE_FUNCTIONS_H
#define READ_WRITE_FUNCTIONS_H
#include "png_structs.h"
#include <QString>
#include <QMainWindow>

void write_png_file(struct Png* image, QString file_name);
int read_png_file(struct Png* image, QString filename, QMainWindow* win);

#endif // READ_WRITE_FUNCTIONS_H
