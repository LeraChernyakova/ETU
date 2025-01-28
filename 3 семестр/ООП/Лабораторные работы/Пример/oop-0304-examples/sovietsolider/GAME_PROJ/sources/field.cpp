#include "../headers/field.h"
#include <iostream>

Field::Field(int size_x, int size_y)
{
    this->size_x = size_x+2; this->size_y = size_y+2;
    generate_field();
}

Field::~Field()
{
    if(field)
    {
        for(int i=0;i<size_y;i++)
        {
            delete [] field[i];
        }
        delete[] field;
    }
}
Field::Field(const Field &other)
{
    size_x = other.size_x; size_y = other.size_y;

    field = new Cell* [size_y];

    for(int i = 0;i<size_y;i++)
    {
        field[i] = new Cell[size_x];
        std::copy(other.field[i], other.field[i]+size_x, field[i]);
    }
}

Field::Field(Field&& other)
{
    std::swap(size_x, other.size_x);
    std::swap(size_y, other.size_y);
    std::swap(field, other.field);
}
Field& Field::operator= (const Field &other)
{
    if(this == &other)
        return *this;

    size_x = other.get_size_x(); size_y = other.get_size_y();

    delete[] field;

    field = new Cell* [size_y];

    for(int i = 0;i<size_y;i++)
    {
        field[i] = new Cell[size_x];
        std::copy(other.field[i], other.field[i]+size_x, field[i]);
    }
    return *this;
}

Field& Field::operator=(Field&& other)
{
    if(this == &other)
        return *this;

    std::swap(size_x, other.size_x);
    std::swap(size_y, other.size_y);

    std::swap(field, other.field);
    return *this;

}
void Field::generate_field()
{
    field = new Cell* [size_y];
    for(int i=0; i<size_y; i++)
    {
        field[i] = new Cell [size_x];
        for(int j=0; j<size_x; j++)
        {
            field[i][j].set_x(j);
            field[i][j].set_y(i);
            if(i == 0 || i==size_y-1)
            {
                field[i][j].set_passable(0);
                field[i][j].set_display('@');
                field[i][j].set_isWall(true);
            }
            else
            {
                field[i][0].set_passable(0);field[i][0].set_display('@'); field[i][0].set_isWall(true);
                field[i][size_x-1].set_passable(0);field[i][size_x-1].set_display('@'); field[i][size_x-1].set_isWall(true);
            }
        }
    }
}

void Field::generate_exits(int &exit_x, int &exit_y)
{
    std::mt19937 generator;
    std::random_device rd;
    generator.seed(rd());
    std::uniform_int_distribution<> dist_side(0, 3);
    std::uniform_int_distribution<> rand_num(0,1);

    int side = dist_side(generator);
    //std::cout << side << '\n';
    if(side == 0 || side == 2)
    {
        std::uniform_int_distribution<> dist_y(1, size_y-2);
        exit_y = dist_y(generator);
        if(rand_num(generator))
            exit_x = 0;
        else
            exit_x = size_x-1;
    }
    else
    {
        if(rand_num(generator))
            exit_y = size_y-1;
        else
            exit_y = 0;

        std::uniform_int_distribution<> dist_x(1, size_x-2);
        exit_x = dist_x(generator);
    }
}

void Field::generate_entrance(int &entrance_x, int &entrance_y)
{
    std::mt19937 generator;
    std::random_device rd;
    generator.seed(rd());
    std::uniform_int_distribution<> dist_side(0, 3);
    std::uniform_int_distribution<> rand_num(0,1);

    int side = dist_side(generator);
    //std::cout << side << '\n';
    if(side == 0 || side == 2)
    {
        std::uniform_int_distribution<> dist_y(1, size_y-2);
        entrance_y = dist_y(generator);
        if(rand_num(generator))
            entrance_x = 0;
        else
            entrance_x = size_x-1;
    }
    else
    {
        if(rand_num(generator))
            entrance_y = size_y-1;
        else
            entrance_y = 0;

        std::uniform_int_distribution<> dist_x(1, size_x-2);
        entrance_x = dist_x(generator);
    }
}

Cell& Field::put_exits(int dist)
{
    

    do
    {
        generate_entrance(entrance_x, entrance_y);
        generate_exits(exit_x, exit_y);
    } while(std::abs(exit_x-entrance_x) <= dist || std::abs(exit_y-entrance_y) <= dist );

    //std::cout << exit_x << " " << exit_y << std::endl;
    //std::cout << entrance_x << " " << entrance_y << std::endl;

    field[exit_y][exit_x].set_display('O');
    field[exit_y][exit_x].set_exit(true);
    field[exit_y][exit_x].set_passable(true);
    field[entrance_y][entrance_x].set_display('E');
    field[entrance_y][entrance_x].set_entrance(true);
    return field[entrance_y][entrance_x];
}

Cell& Field::generate_enemy()
{
    std::mt19937 generator;
    std::random_device rd;
    generator.seed(rd());
    std::uniform_int_distribution<> pos_x(1, size_x-2);
    std::uniform_int_distribution<> pos_y(1, size_y-2);
    int x, y, i=0;
    do
    {
        x = pos_x(generator);
        y = pos_y(generator);
        i++;
        //std::cout << x << ' ' << y << std::endl;
    } while (check_for_enemies(x, y));
    //field[y][x].set_passable(false);
    return field[y][x];
}

bool Field::check_for_enemies(int x, int y)
{
    return (field[y][x].get_has_enemy() || field[y][x].get_has_object()
    || field[y][x].get_has_player() || !field[y][x].get_passable() || std::abs(entrance_x-field[y][x].get_x()) < 2 || std::abs(entrance_y-field[y][x].get_y())<2
    || field[y+1][x].get_has_enemy() || field[y-1][x].get_has_enemy() || field[y][x+1].get_has_enemy()
    || field[y][x-1].get_has_enemy() || field[y+1][x+1].get_has_enemy() || field[y+1][x-1].get_has_enemy()
    || field[y-1][x+1].get_has_enemy() || field[y-1][x-1].get_has_enemy());
}
void Field::put_enemies(std::vector<Enemy*>enemy_container)
{
    size_t passable_cells = 0;
    for(size_t x = 0; x < size_x; ++x)
        for(size_t y = 0; y < size_y; ++y)
            if(field[y][x].get_passable())
                passable_cells++;

    for(int i =0; i<std::min(enemy_container.size(), passable_cells / 9); i++)
    {
        generate_enemy().set_enemy(*(enemy_container.at(i)));
        //enemy_container.at(i)->add_enemy(generate_enemy());
    }
}

Cell& Field::generate_objects()
{
    std::mt19937 generator;
    std::random_device rd;
    generator.seed(rd());
    std::uniform_int_distribution<> pos_x(1, size_x-2);
    std::uniform_int_distribution<> pos_y(1, size_y-2);
    int x, y, i=0;
    do
    {
        x = pos_x(generator);
        y = pos_y(generator);
        i++;
        //std::cout << x << ' ' << y << std::endl;
    } while (check_for_objects(x, y));
    //field[y][x].set_passable(false);
    return field[y][x];    
}

bool Field::check_for_objects(int x, int y)
{
    return (field[y][x].get_has_enemy() || field[y][x].get_has_object()
    || field[y][x].get_has_player() || !field[y][x].get_passable() || field[y+1][x].get_has_enemy() 
    || field[y-1][x].get_has_enemy() || field[y][x+1].get_has_enemy()
    || field[y][x-1].get_has_enemy() || field[y+1][x+1].get_has_enemy() || field[y+1][x-1].get_has_enemy()
    || field[y-1][x+1].get_has_enemy() || field[y-1][x-1].get_has_enemy());
}

void Field::put_object(std::vector<Object*>object_container)
{
    for(int i =0; i<object_container.size(); i++)
    {
        generate_objects().set_object(*(object_container.at(i)));
        //object_container.at(i)->addObject(generate_objects());
    }
}


int Field::get_size_x() const
{
    return size_x;
}

int Field::get_size_y() const
{
    return size_y;
}

Cell& Field::get_cell(int x, int y)
{
    if(x>size_x || y>size_y)
        throw "coordinates are out of bounds";
    return field[y][x];

}
