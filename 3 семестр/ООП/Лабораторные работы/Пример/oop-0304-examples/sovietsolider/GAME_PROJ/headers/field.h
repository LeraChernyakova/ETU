#ifndef FIELD_H
#define FIELD_H
#include "cell.h"
#include <random>
#include <tuple>
#include "object.h"
//#include "enemyInterface.h"

class Enemy;

class Field
{
private:
    Cell** field = nullptr;
    int size_x, size_y;
    int entrance_x, entrance_y, exit_x, exit_y;
public:
    Field(int size_x, int size_y);
    Field(const Field &other);
    Field(Field &&other);
    ~Field();

    Field& operator=(const Field& other);
    Field& operator=(Field&& other);

    int get_size_x() const;
    int get_size_y() const;
    Cell& get_cell(int x, int y);

    void generate_field();
    void generate_exits(int &exit_x, int &exit_y);
    void generate_entrance(int &entrance_x, int &entrance_y);
    void generate_walls();
    Cell& put_exits(int dist);

    Cell& generate_enemy();
    void put_enemies(std::vector<Enemy*>enemies);
    bool check_for_enemies(int x, int y);

    Cell& generate_objects();
    void put_object(std::vector<Object*>objects_container);
    bool check_for_objects(int x, int y);

};

#endif // FIELD_H
