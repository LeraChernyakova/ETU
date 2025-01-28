#include "GameField.h"
#include <iostream>

    GameField::GameField() {
        size_x = 10;
        size_y = 10;
        field_of_cells=new Cell*[size_y];
        for (int i=0;i<size_y;i++)
            field_of_cells[i]=new Cell[size_x];
        for (int i=0;i<size_y;i++){
            for (int j=0;j<size_x;j++) {
                Cell one(false, false);
                field_of_cells[i][j]=one;
            }
        }
        field_of_cells[0][0].changeEvent(true);
    }

    GameField::GameField(int size_x, int size_y): size_x(size_x), size_y(size_y){
        field_of_cells=new Cell*[size_y];
        for (int i=0;i<size_y;i++)
            field_of_cells[i]=new Cell[size_x];
        for (int i=0;i<size_y;i++){
            for (int j=0;j<size_x;j++) {
                Cell one(false, false);
                field_of_cells[i][j]=one;
            }
        }
        field_of_cells[0][0].changeEvent(true);
    }

    GameField::~GameField(){
        for (int i=0;i<size_y;i++) delete[] field_of_cells[i];
        delete []field_of_cells;
    }

    GameField::GameField(const GameField & field): size_x(field.size_x), size_y(field.size_y), player_x(field.player_x), player_y(field.player_y){
        field_of_cells=new Cell*[size_y];
        for (int i=0;i<size_y;i++)
            field_of_cells[i]=new Cell[size_x];
        for (int i=0;i<size_y;i++){
            for (int j=0;j<size_x;j++) {
                Cell one(false, false);
                field_of_cells[i][j]=one;
            }
        }
        field_of_cells[0][0].changeEvent(true);
    }

    GameField::GameField(GameField&& field) noexcept{
        std::swap(size_x, field.size_x);
        std::swap(size_y, field.size_y);
        std::swap(player_x, field.player_x);
        std::swap(player_y, field.player_y);
        std::swap(field_of_cells, field.field_of_cells);
    }

    GameField &GameField::operator=(const GameField &field){
    if (this!=&field){
        for (int i=0;i<size_y;i++) delete[] field_of_cells[i];
        delete []field_of_cells;
        size_x=field.size_x;
        size_y=field.size_y;
        player_x=field.player_x;
        player_y=field.player_y;
        field_of_cells=new Cell*[size_y];
        for (int i=0;i<size_y;i++)
            field_of_cells[i]=new Cell[size_x];
        for (int i=0;i<size_y;i++){
            for (int j=0;j<size_x;j++) {
                Cell one(false, false);
                field_of_cells[i][j]=one;
            }
        }
        field_of_cells[0][0].changeEvent(true);
    }
    return *this;
}

    GameField &GameField::operator=(GameField &&field) noexcept{
    if (this!=&field){
        std::swap(size_x, field.size_x);
        std::swap(size_y, field.size_y);
        std::swap(player_x, field.player_x);
        std::swap(player_y, field.player_y);
        std::swap(field_of_cells, field.field_of_cells);
    }
    return *this;
}
    int GameField::getPlayerX(){
        return player_x;
    }
    int GameField::getPlayerY(){
        return player_y;
    }
    int GameField::getSizeY(){
        return size_y;
    }
    int GameField::getSizeX(){
        return size_x;
    }
    Cell** GameField::getField(){
        return field_of_cells;
    }
    void GameField::changeData(int x_change, int y_change){
        field_of_cells[player_y][player_x].changeEvent(false);
        player_y+=y_change;
        player_x+=x_change;
        player_y = (size_y + player_y) % size_y;
        player_x = (size_x + player_x) % size_x;
        field_of_cells[player_y][player_x].changeEvent(true);
    }

    void GameField::doOccasions(Player& player, Union union1){//вызывается реакция события на игрока
        if ((player_y!=size_y-1) and (player_x!=size_x-1))//проверка на выходе ли игрок
            field_of_cells[player_y][player_x].getOccasion()->react(player, union1);
    }
