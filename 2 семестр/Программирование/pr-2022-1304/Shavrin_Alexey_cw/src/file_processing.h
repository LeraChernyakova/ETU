#pragma once

int read_input_file(Configs *comnfig, File *file, BitmapFileHeader *bmfh, BitmapInfoHeader *bmih);
int create_output_file(Configs *config, File *file);
