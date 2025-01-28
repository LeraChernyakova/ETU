#include "png_structs.h"
#include <QMessageBox>
#include <QMainWindow>

int read_png_file(struct Png* image, QString file_name, QMainWindow* win) {

    int y;
    png_byte header[8];    // 8 is the maximum size that can be checked
    QByteArray ba = file_name.toLocal8Bit();
    const char *c_str = ba.data();

    /* open file and test for it being a png */
    FILE *fp = fopen(c_str, "rb");
    if (!fp){
        QMessageBox::critical(win, "Ошибка", "Файл не может быть открыт.");
        return 0;
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)){
        QMessageBox::critical(win, "Ошибка", "Тип файла не PNG");
        return 0;
    }

    /* initialize stuff */
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        QMessageBox::critical(win, "Ошибка", "Ошибка чтения файла. Проверьте корректность переданного файла.");
        return 0;
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        QMessageBox::critical(win, "Ошибка", "Ошибка чтения файла. Проверьте корректность переданного файла.");
        return 0;
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        QMessageBox::critical(win, "Ошибка", "Ошибка чтения файла. Проверьте корректность переданного файла.");
        return 0;
    }

    png_init_io(image->png_ptr, fp); // init input/output
    png_set_sig_bytes(image->png_ptr, 8); // libpng needs to know that some chuncks were readen (in png_sig_cmp)

    png_read_info(image->png_ptr, image->info_ptr); // process chuncks

    /* now we can easy query the info structure above
    this do the following functions: */

    image->width = png_get_image_width(image->png_ptr, image->info_ptr); // width
    image->height = png_get_image_height(image->png_ptr, image->info_ptr); // height
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr); // color type
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr); // bit depth


    png_read_update_info(image->png_ptr, image->info_ptr); // after that we can read image row by row

    /* read file */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        QMessageBox::critical(win, "Ошибка", "Ошибка чтения файла. Проверьте корректность переданного файла.");
        return 0;
    }

    // allocate memory for storing image
    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    for (y = 0; y < image->height; y++)
        image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    // reading image
    png_read_image(image->png_ptr, image->row_pointers);

    if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB){
        image->pixel_width = 3;
    } else {
        QMessageBox::critical(win, "Ошибка", "Входной файл должен принадлежать формату RGBA.");
        return 0;
    }
    fclose(fp);
    return 1;
}

void write_png_file(struct Png* image, QString file_name) {
    int y;

    QByteArray ba = file_name.toLocal8Bit();
    const char *c_str = ba.data();

    /* create file */
    FILE *fp = fopen(c_str, "wb");


    /* initialize stuff */
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    image->info_ptr = png_create_info_struct(image->png_ptr);

    png_init_io(image->png_ptr, fp);


    /* now we need fill in the png_info structure with all data
    we wish to write before the actual image. */
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);


    png_write_image(image->png_ptr, image->row_pointers);

    png_write_end(image->png_ptr, NULL);

    /* cleanup heap allocation */
    for (y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);

    fclose(fp);
}
