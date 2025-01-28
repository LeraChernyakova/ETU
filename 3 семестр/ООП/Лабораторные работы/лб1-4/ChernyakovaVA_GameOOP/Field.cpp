#include "Field.h"

Field::Field(int a, int b) : width(a), height(b), player_position({ 0,0 }), count_free_cells(width* height - 1), player(
    nullptr), win_cell_position({a-1, b-1}) {
    for (int i = 0; i < height; ++i) {
        field.emplace_back();
        for (int j = 0; j < width; ++j) {
            field.at(i).emplace_back();
        }
    }
}

void Field::swap(Field& other) {
    std::swap(height, other.height);
    std::swap(width, other.width);
    std::swap(field, other.field);
    std::swap(player_position, other.player_position);
    std::swap(observers, other.observers);
    std::swap(player, other.player);
}

Field& Field::operator=(Field&& other) noexcept{
    if (this != &other) {
        this->swap(other);
    }
    return *this;
}

Field::Field(const Field& other): width(other.width), height(other.height), player_position(other.player_position), player(other.player) {
    for (int i = 0; i != height; i++)
    {
        this->field.emplace_back();
        for (int j = 0; j != width; j++)
        {
            this->field.at(i).push_back(other.field.at(i).at(j));
        }
    }
}

Field::Field(Field&& other) {
    this->swap(other);
}

Field& Field::operator=(const Field& other) {
    if (this != &other)
        Field(other).swap(*this);

    return *this;
}

void Field::set_field(std::vector<std::vector<Cell>>& fl) {
    deconstruct();
    field = fl;
    height = (int)field.size();
    width = (int)field.at(0).size();
    count_frees();
    notify();
}

void Field::change_player_position(Player::Moves direction) {

    std::pair<int, int> temp = player_position;

    switch (direction) {
    case Player::UP:
        temp.second--;
        break;
    case Player::DOWN:
        temp.second++;
        break;
    case Player::LEFT:
        temp.first--;
        break;
    case Player::RIGHT:
        temp.first++;
        break;
    }
    temp.first = temp.first % width;
    temp.second = temp.second % height;
    if (temp.first < 0) temp.first += width;
    if (temp.second < 0) temp.second += height;

    check_position(temp);
    notify();
    if (field.at(player_position.second).at(player_position.first).get_event() != nullptr) {
        MessageFactory::get_instance().create_message(GameObjects, "Event started!");
        field.at(player_position.second).at(player_position.first).get_event()->execute();
        field.at(player_position.second).at(player_position.first).set_event(nullptr);
    }
}


void Field::remove_walls() {
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != width; ++j) {
            field.at(i).at(j).set_wall(false);
        }
    }
    this->notify();
    MessageFactory::get_instance().create_message(GameObjects, "Walls have been removed from the playing field.");
}

int Field::get_height() const {
    return this->height;
};

int Field::get_width() const {
    return this->width;
}

Cell& Field::get_cell(int x, int y) {
    return field.at(y).at(x);
}

void Field::check_position(std::pair<int, int> pair) {
    if (field.at(pair.second).at(pair.first).is_wall()) {
        MessageFactory::get_instance().create_message(Errors, "The player tried to step on the wall.");
        return;
    }
    this->player_position = pair;
}

void Field::deconstruct() {
    if (field.empty()) {
        return;
    }
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != width; ++j) {
            field.at(i).at(j).set_event(nullptr);
        }
        field.at(i).clear();
    }
    field.clear();
}

Field::~Field() {
    deconstruct();
}

std::pair<int, int> Field::get_position() const {
    return player_position;
}

void Field::set_player_pos(std::pair<int, int>& pos) {
    player_position = std::move(pos);
}

int Field::get_count_free() const {
    return count_free_cells;
}

void Field::set_count(int count) {
    count_free_cells = count;
}

void Field::set_player(Player* pl) {
    player = pl;
}

Player* Field::get_player() const {
    return player;
}

void Field::count_frees() {
    count_free_cells = 0;
    for (const auto& row : field) {
        for (auto cell : row) {
            if (cell.is_wall() || cell.get_event() != nullptr)
                continue;
            count_free_cells++;
        }
    }
    count_free_cells--;
}

void Field::set_win_cell_pos(std::pair<int, int>& pos) {
    win_cell_position = std::move(pos);
}

std::pair<int, int> Field::get_win_cell_position() {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (dynamic_cast<TreasureEvent*>(this->get_cell(j, i).get_event()) != nullptr) {
                this->win_cell_position.first = j;
                this->win_cell_position.second = i;
            }
        }
    }
    return this->win_cell_position;
}

void Field::check_way() {
    int p_p_x = player_position.first, p_p_y = player_position.second;
    int w_c_x = win_cell_position.first, w_c_y = win_cell_position.first;

    if (p_p_x == w_c_x) {
        if (p_p_y < w_c_y) {
            for (int i = p_p_y+1; i < w_c_y; i++)
                this->get_cell(p_p_x, i).set_wall(false);
        }
        else {
            for (int i = w_c_y + 1; i < p_p_y; i++)
                this->get_cell(p_p_x, i).set_wall(false);
        }
    }

    if (p_p_y == w_c_y) {
        if (p_p_x < w_c_x) {
            for (int i = p_p_x + 1; i < w_c_x; i++)
                this->get_cell(i, p_p_y).set_wall(false);
        }
        else {
            for (int i = w_c_x + 1; i < p_p_x; i++)
                this->get_cell(i, p_p_y).set_wall(false);
        }
    }

    if (p_p_y < w_c_y) {
        if (p_p_x < w_c_x) {
            for (int i = p_p_y; i < w_c_y; i++) {
                for (int j = p_p_x + 1; j <= w_c_x; j++) {
                    if (i == p_p_y) {
                        this->get_cell(j, i).set_wall(false);
                    }
                    else if (j == w_c_x) {
                        this->get_cell(j, i).set_wall(false);
                    }
                }
            }
        }
        else {
            for (int i = w_c_y; i > p_p_y; i--) {
                for (int j = w_c_x + 1; j <= p_p_x; j++) {
                    if (i == w_c_y) {
                        this->get_cell(j, i).set_wall(false);
                    }
                    else if (j == p_p_x) {
                        this->get_cell(j, i).set_wall(false);
                    }
                }
            }
        }
    }

    if (p_p_y > w_c_y) {
        if (p_p_x < w_c_x) {
            for (int i = p_p_y; i > w_c_y; i--) {
                for (int j = p_p_x + 1; j <= w_c_x; j++) {
                    if (i == p_p_y) {
                        this->get_cell(j, i).set_wall(false);
                    }
                    else if (j == w_c_x) {
                        this->get_cell(j, i).set_wall(false);
                    }
                }
            }
        }
        else {
            for (int i = p_p_y; i > w_c_y; i--) {
                for (int j = p_p_x + 1; j >= w_c_x; j--) {
                    if (i == p_p_y) {
                        this->get_cell(j, i).set_wall(false);
                    }
                    else if (j == w_c_y) {
                        this->get_cell(j, i).set_wall(false);
                    }
                }
            }
        }
    }
}



