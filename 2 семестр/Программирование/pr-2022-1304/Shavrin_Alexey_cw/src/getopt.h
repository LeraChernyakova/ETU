#pragma once

void PrintHelp();
int is_number(char *arg);
int is_rgb_numbers(int args[]);
int read_args(int argc, char *argv[], int *optind, int count, int args[]);

