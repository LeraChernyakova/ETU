#include "Util_Funcs.h"

bool check_pos(int point, int length) {
    return (point < 0 || point > length);
}
void placer(Cell& cell, bool with_force) {
    if (with_force) {
        cell.set_event(nullptr);
    }
    cell.set_wall(true);
}
int new_count(int cur_count, int free_cells) {
    double count = cur_count;
    double percent = (double)count / free_cells;
    while (percent > 0.3) {
        count /= 1.2;
        percent = count / free_cells;
    }
    return (int)count;
}