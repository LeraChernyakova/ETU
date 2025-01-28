#ifndef CELL_H
#define CELL_H
#include <iostream>
#include "cellObject.h"
#include "object.h"
#include "enemy.h"
#include "player.h"
#include "cellView.h"


class Cell
{
private:
    CellObject* stored_object = nullptr;
    CellObject* enemy = nullptr;
    CellObject* player = nullptr;
    CellView* cv;
    bool passable = 1;
    bool exit = 0, entrance = 0, wall = 0;
    char display = '*';
    int x = 0, y = 0;
protected:
public:
    Cell();
    //~Cell();
    void set_display(char ch);
    CellView& get_display();

    void set_exit(bool state);
    bool get_exit();

    void set_entrance(bool state);
    bool get_entrance();

    void set_passable(bool state);
    bool get_passable();

    void set_object(Object& object);
    void clear_object();
    //void set_object(CellObject* object);
    CellObject& get_object();
    bool get_has_object();

    void set_player(Player& player);
    CellObject& get_player();
    bool get_has_player();
    void clear_player();

    void set_enemy(Enemy& enemy);
    CellObject& get_enemy();
    bool get_has_enemy();
    void clear_enemy();

    void set_x(int x);
    int get_x();

    void set_y(int y);
    int get_y();

    void set_isWall(bool state);
    bool isWall();

    
    
};

#endif // CELL_H
