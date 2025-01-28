#pragma once

int is_bmp(char *arg);
int case_input_file(Configs *config, char *optarg);
int case_output_file(Configs *config, char *optarg);
int search_input_file(int argc, char *argv[], int *optind, Configs *config);
void no_input_file();
