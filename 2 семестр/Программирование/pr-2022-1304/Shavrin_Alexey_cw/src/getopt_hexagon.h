#pragma once

int case_hexstart(int argc, char *argv[], int *optind, Configs *config, Hexagon *hexagon);
int case_hexend(int argc, char *argv[], int *optind, Configs *config, Hexagon *hexagon);
int case_hexcenter(int argc, char *argv[], int *optind, Configs *config, Hexagon *hexagon);
int case_hexradius(int argc, char *argv[], char *optarg, Configs *config, Hexagon *hexagon);
int case_hexline_width(int argc, char *argv[], char *optarg, Configs *config, Hexagon *hexagon);
int case_hexline_color(int argc, char *argv[], int *optind, Configs *config, Hexagon *hexagon);
int case_hexfilling(int argc, char *argv[], int *optind, Configs *config, Hexagon *hexagon);
