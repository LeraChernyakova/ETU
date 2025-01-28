#pragma once

class Cell;

#include "Cell.h"
#include "Player.h"
#include "ISubject.h"
#include "TreasureEvent.h"
#include <functional>
#include <map>
#include <vector>
#include <utility>
#include "LogPool.h"

class Field : public ISubject {
private:
    int height;
    int width;
    int count_free_cells;
    Player* player;
    std::pair<int, int> player_position;
    std::vector<std::vector<Cell>> field;
    void check_position(std::pair<int, int> pair);
    std::vector<IObserver*> observers;
    void count_frees();
    std::pair<int, int> win_cell_position;
public:
    explicit Field(int a = 10, int b = 10);
    Field(const Field& other);
    Field(Field&& other);
    void swap(Field& other);
    Field& operator=(const Field& other);
    Field& operator=(Field&& other) noexcept;
    void set_field(std::vector<std::vector<Cell>>& fl);
    void set_player_pos(std::pair<int, int>& pos);
    void change_player_position(Player::Moves direction);
    int get_height() const;
    int get_width() const;
    int get_count_free() const;
    void set_count(int count);
    void set_player(Player* pl);
    Player* get_player() const;
    Cell& get_cell(int x, int y);
    std::pair<int, int> get_position() const;
    void remove_walls();
    void deconstruct();
    void set_win_cell_pos(std::pair<int, int>& pos);
    std::pair<int, int> get_win_cell_position();
    void check_way();
    ~Field();
};