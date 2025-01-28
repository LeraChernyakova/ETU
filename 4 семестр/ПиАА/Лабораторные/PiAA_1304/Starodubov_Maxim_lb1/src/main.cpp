#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <tuple>


/*
 * the piece is defined as the coordinates of its upper left corner
 * and the size of its side, these parameters are stored in the tuple
 */
typedef std::tuple<unsigned, unsigned, unsigned> piece_t;
/*
 * position is defined as x and y coordinates, stored in pair
 */
typedef std::pair<unsigned, unsigned> position_t;


/*
 * class Desk describing the desk on which the pieces are placed
 */
class Desk
{
public:
    explicit Desk(unsigned size);
    Desk(const Desk &other);

    void add_piece(unsigned size);
    void add_piece(unsigned size, position_t position);
    std::vector<piece_t> get_pieces();
    unsigned get_max_piece_size() const;
    unsigned get_number_of_pieces() const;
    bool is_filled() const;

private:
    /*
     * desk side size
     */
    unsigned _size;
    /*
     * coordinates of the upper left free position
     */
    position_t _next_unfilled_position;
    /*
     * the maximum size of a piece that can be placed in the upper left free position
     */
    unsigned _max_piece_size;
    /*
     * vector of pieces that located on the desk
     */
    std::vector<piece_t> _pieces;

    void set_piece(bool positions[], piece_t &piece) const;
    void update_next_position(const bool positions[]);
    void update_max_piece_size(const bool positions[]);

};


/*
 * desk is defined by the size of its side
 */
Desk::Desk(unsigned size)
{
    _size = size;
    _max_piece_size = _size - 1;
    _next_unfilled_position = {0, 0};
    _pieces.reserve(2 * ((_size + 1) / 2 + 1));
}

/*
 * copy constructor
 */
Desk::Desk(const Desk &other)
{
    _size = other._size;
    _max_piece_size = other._max_piece_size;
    _next_unfilled_position = other._next_unfilled_position;

    _pieces.reserve(2 * ((_size + 1) / 2 + 1));
    for (auto &piece: other._pieces)
    {
        _pieces.emplace_back(std::get<0>(piece), std::get<1>(piece), std::get<2>(piece));
    }
}

/*
 * adding a piece to the left top free position
 */
void Desk::add_piece(unsigned size)
{
    add_piece(size, _next_unfilled_position);
}

/*
 * adding a piece to a given position
 */
void Desk::add_piece(unsigned size, position_t position)
{
    _pieces.emplace_back(position.first, position.second, size);

    bool positions[_size][_size];
    for (unsigned i = 0; i < _size; i++)
    {
        for (unsigned j = 0; j < _size; j++)
        {
            positions[i][j] = false;
        }
    }

    for (auto &piece: _pieces)
    {
        set_piece((bool *) positions, piece);
    }

    update_next_position((bool *) positions);
    update_max_piece_size((bool *) positions);

}

/*
 * methods needed to determine the top left free position and the maximum size of a piece
 * that can be placed on it after adding the next piece to the desk
 */
void Desk::set_piece(bool positions[], piece_t &piece) const
{
    unsigned position_x = std::get<0>(piece);
    unsigned position_y = std::get<1>(piece);
    unsigned piece_size = std::get<2>(piece);
    for (unsigned y = position_y; y < position_y + piece_size; y++)
    {
        for (unsigned x = position_x; x < position_x + piece_size; x++)
        {
            positions[_size * y + x] = true;
        }
    }
}

void Desk::update_next_position(const bool positions[])
{
    unsigned position_x = _next_unfilled_position.first;
    unsigned position_y = _next_unfilled_position.second;

    for (unsigned i = _size * position_y + position_x; i < _size * _size; i++)
    {
        if (!positions[i])
        {
            _next_unfilled_position = {i % _size, i / _size};
            return;
        }
    }
    _next_unfilled_position = {_size, _size};
}

void Desk::update_max_piece_size(const bool positions[])
{
    unsigned position_x = _next_unfilled_position.first;
    unsigned position_y = _next_unfilled_position.second;

    _max_piece_size = position_x + position_y == 0 ? _size - 1 : std::min(_size - position_x, _size - position_y);
    for (unsigned i = 0; i < std::min(_size - position_x, _size - position_y); i++)
    {
        if (positions[_size * (position_y + i) + position_x] || positions[_size * position_y + position_x + i])
        {
            _max_piece_size = i;
            break;
        }
    }
}

/*
 * returns a vector containing the pieces located on the desk
 */
std::vector<piece_t> Desk::get_pieces()
{
    return _pieces;
}

/*
 * returns the maximum size of a piece's side that can be placed in the top left free position
 */
unsigned Desk::get_max_piece_size() const
{
    return _max_piece_size;
}

/*
 * returns the number of pieces located on the desk
 */
unsigned Desk::get_number_of_pieces() const
{
    return _pieces.size();
}

/*
 * returns true if there are no empty positions left on the desk
 */
bool Desk::is_filled() const
{
    unsigned position_x = _next_unfilled_position.first;
    unsigned position_y = _next_unfilled_position.second;
    return position_y == _size || position_x == _size;
}


/*
 * class Solver defines methods that solve the task
 */
class Solver
{
public:
    std::vector<piece_t> solve(unsigned n);

private:
    std::pair<unsigned, unsigned> factorize(unsigned n);
    void get_trivial_solution(Desk &desk, unsigned desk_size);
    void add_possible_start_positions(std::stack<Desk> &stack, unsigned desk_size);

};


/*
 * the main algorithm for solving the task
 */
std::vector<piece_t> Solver::solve(unsigned n)
{
    std::pair<unsigned, unsigned> multipliers = factorize(n);
    unsigned desk_size = multipliers.first;
    unsigned pieces_multiplier = multipliers.second;

    unsigned record = 2 * ((desk_size + 1) / 2 + 1);
    Desk solution(desk_size);
    get_trivial_solution(solution, desk_size);

    std::stack<Desk> stack;
    add_possible_start_positions(stack, desk_size);

    while (!stack.empty())
    {
        Desk &current_desk = stack.top();

        if (current_desk.is_filled() && current_desk.get_number_of_pieces() < record)
        {
            record = current_desk.get_number_of_pieces();
            solution = current_desk;
            stack.pop();
            continue;
        }

        if (current_desk.get_number_of_pieces() + 1 >= record)
        {
            stack.pop();
            continue;
        }

        for (unsigned i = 2; i <= current_desk.get_max_piece_size(); i++)
        {
            stack.emplace(current_desk);
            Desk &new_desk = stack.top();
            new_desk.add_piece(i);
        }
        current_desk.add_piece(1);

    }

    std::vector<piece_t> solution_pieces = solution.get_pieces();
    for (auto &piece: solution_pieces)
    {
        std::get<0>(piece) = std::get<0>(piece) * pieces_multiplier + 1;
        std::get<1>(piece) = std::get<1>(piece) * pieces_multiplier + 1;
        std::get<2>(piece) *= pieces_multiplier;
    }

    return solution_pieces;
}

/*
 * methods needed to optimize the algorithm
 */
std::pair<unsigned, unsigned> Solver::factorize(unsigned n)
{
    for (unsigned divider = 2; divider <= unsigned(std::sqrt(n)); divider++)
    {
        if (n % divider == 0)
        {
            return {divider, n / divider};
        }
    }
    return {n, 1};
}

void Solver::get_trivial_solution(Desk &desk, unsigned desk_size)
{
    desk.add_piece((desk_size + 1) / 2);
    for (unsigned i = 0; i < 3; i++)
    {
        desk.add_piece(desk_size / 2);
    }
    while (!desk.is_filled())
    {
        desk.add_piece(1);
    }
}

void Solver::add_possible_start_positions(std::stack<Desk> &stack, unsigned desk_size)
{
    for (unsigned i = 2; i <= desk_size / 2; i++)
    {
        stack.emplace(desk_size);
        Desk &current_desk = stack.top();
        current_desk.add_piece(desk_size - i);
        for (unsigned j = 0; j < (desk_size - i) / i; j++)
        {
            current_desk.add_piece(i, {desk_size - i, i * j});
            current_desk.add_piece(i, {i * j, desk_size - i});
        }
    }
}

int main()
{
    unsigned n;
    std::cin >> n;
    Solver solver;
    auto solution = solver.solve(n);

    std::cout << solution.size() << '\n';
    for (auto &piece: solution)
    {
        std::cout << std::get<0>(piece) << ' ' << std::get<1>(piece) << ' ' << std::get<2>(piece) << '\n';
    }

    return 0;
}
