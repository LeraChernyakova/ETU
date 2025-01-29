#include <iostream>
#include <vector>

#define EVEN_COUNT 4
#define FIRST_ORDINAL_NUM_SQUARE 4
#define THREE_COUNT 6


//Структура, отвечаящая за хранение разбиения
typedef struct {
    int min_count_square;
    std::vector<std::vector<int>> square_matrix;
    int size;
} Square;

//Структура, отвечающая за хранение требуемого формата ответа
typedef struct {
    int count_square;
    std::vector<std::vector<int>> coordinates_and_size_squares;
} Answer;

// Структура, отвечающая за хранение координат первой встретившийся пустой клетки
typedef struct {
    int x = 0;
    int y = 0;
    bool is_empty = false; //Флаг, отвечающий за то, нашлась ли пустая клетка
}Point;

//Функция, печатающая ответ в необходимом формате
//На вход принимает объект типа Answer
void print_answer(Answer answer) {
    std::cout << answer.count_square << std::endl;
    for (int i = 0; i < answer.coordinates_and_size_squares.size(); i++){
        std::cout << answer.coordinates_and_size_squares[i][0] << " " << answer.coordinates_and_size_squares[i][1] << " " << answer.coordinates_and_size_squares[i][2] << std::endl;
    }
}

//Функция, конвертирующая данные из объекта типа Square
//в данные типа Answer
//На вход принимает объект типа Square, возвращает объект типа Answer
Answer converting_answer(Square square){
    Answer answer;
    answer.count_square = square.min_count_square;
    
    for(int y = 0; y < square.size; y++){
        for(int x = 0; x < square.size; x++){
            if(square.square_matrix[y][x] != 0){
                int num = square.square_matrix[y][x];
                int count = 0;
                for(int i = x; i < square.size; i++){
                    if(square.square_matrix[y][i] == num){
                        count++;
                    }
                }
                answer.coordinates_and_size_squares.push_back({y + 1, x + 1, count});
                for(int y1 = 0; y1 < square.size; y1++){
                    for(int x1 = 0; x1 < square.size; x1++){
                        if(square.square_matrix[y1][x1] == num){
                            square.square_matrix[y1][x1] = 0;
                        }
                    }
                }
            }
        }
    }
    return answer;
}


//Функция, которая находит решение для доски с четной стороной
//На вход получает размер доски, возвращает объект типа Answer
Answer even_size(int size) {
    Answer answer;
    answer.count_square = EVEN_COUNT;
    for (int y = 0; y < answer.count_square / 2; y++){
        for (int x = 0; x < answer.count_square / 2; x++){
            answer.coordinates_and_size_squares.push_back({ y * size / 2 + 1, x * size / 2 + 1, size / 2 });
        }
    }
    return answer;
}

//Функция, которая ищет координаты первой встретившейся пустой ячейки
//На вход получает объект типа Square
//Возвращает объект типа Point, в котором хранится координата первой встретившейся пустой ячеейки
Point find_empty_coord(Square tmp_sq){
    Point point_corner;
    for (int y = tmp_sq.size / 2; y < tmp_sq.size; y++){
        for (int x = tmp_sq.size / 2; x < tmp_sq.size; x++){
            if (tmp_sq.square_matrix[y][x] == 0) {
                point_corner.x = x;
                point_corner.y = y;
                point_corner.is_empty = true;
                break;
            }
        }
        if (point_corner.is_empty){
            break;
        }
    }
    return point_corner;
}

//Функция, которая ищет минимальную сторону по x и по y.
//Данная сторона будет максимальной стороной квадрата, который можно вписать в разбиение
//Принимает на вход  объект типа Point и объект типа Square
//Возвраащает целочисленное значение - максимально возможную сторону квадрата, который можно вписать
int find_max_side(Point point_corner, Square tmp_sq){
    int x_side = 0;
    int y_side = 0;
    for (int y = point_corner.y; y < tmp_sq.size; y++) {
        if (tmp_sq.square_matrix[y][point_corner.x] == 0){
            y_side++;
        }
        else{
            break;
        }
    }
    for (int x = point_corner.x; x < tmp_sq.size; x++){
        if (tmp_sq.square_matrix[point_corner.y][x] == 0){
            x_side++;
        }
        else{
            break;
        }
    }
    return std::min(x_side, y_side);
}

//Рекурсивная функция, которая ищет оптимальное разбиение доски
//На вход принимает объект типа Square, который отвечает за текущее оптимальное разбиение,
//объект типа Square, который отвечает за текущее разбиение,
//и целочисленное значение - порядковый номер вставляемого квадрата 
//Возвращает объект типа Square
Square backtracking(Square square, Square tmp_sq, int ordinal_num_square) {
    Point point_corner = find_empty_coord(tmp_sq);
    
    if (!point_corner.is_empty){
        tmp_sq.min_count_square = ordinal_num_square - 1;
        return square.min_count_square < tmp_sq.min_count_square ? square : tmp_sq;
    }
    
    if (ordinal_num_square == square.min_count_square){
        return square;
    }
    
    int min_side = find_max_side(point_corner, tmp_sq);
    for (int size_square = 1; size_square <= min_side; size_square++) {
        for (int y = 0; y < size_square; y++) {
            for (int x = 0; x < size_square; x++) {
                tmp_sq.square_matrix[point_corner.y + y][point_corner.x + x] = ordinal_num_square;
            }
        }
        square = backtracking(square, tmp_sq, ordinal_num_square + 1);
    }
    return square;
}

//Функция, создающее начальное разбиение "раскраску"
//На вход принимает указатель на объект типа Square
void start_splitting(Square* square){
    square->min_count_square = square->size * square->size;
    for (int y = 0; y < square->size; y++) {
        square->square_matrix.push_back(std::vector<int>());
        for (int x = 0; x < square->size; x++) {
            if ((y < (square->size + 1) / 2) && (x < (square->size + 1) / 2)){
                square->square_matrix[y].push_back(1);
            }
            else if ((y < square->size / 2) && (x >= (square->size + 1) / 2)){
                square->square_matrix[y].push_back(2);
            }
            else if ((y >= (square->size + 1) / 2) && (x < square->size / 2)){
                square->square_matrix[y].push_back(3);
            }
            else{
                square->square_matrix[y].push_back(0);
            }
        }
    }

}


//Функция, которая находит решение для доски с нечетной стороной
//На вход получает размер доски, возвращает объект типа Answer
Answer find_splitting(int size) {

    Square square;
    square.size = size;
    start_splitting(&square);

    Square tmp_square;
    tmp_square = square;
    square = backtracking(square, tmp_square, FIRST_ORDINAL_NUM_SQUARE);
    
    return converting_answer(square);
}

//Функция частного решения для доски со стороной кратной 3
//На вход принимает целочисленное значение - сторону доски
//Возвращает объект типа Answer 
Answer multiple_of_three(int size){
    Answer answer;
    answer.count_square = THREE_COUNT;
    int formul = (size / 3) * 2;
    answer.coordinates_and_size_squares.push_back(std::vector<int>({1, 1, formul}));
    answer.coordinates_and_size_squares.push_back(std::vector<int>({formul + 1, 1, formul / 2}));
    answer.coordinates_and_size_squares.push_back(std::vector<int>({1, formul + 1, formul / 2}));
    answer.coordinates_and_size_squares.push_back(std::vector<int>({formul + 1, formul / 2 +1 , formul / 2}));
    answer.coordinates_and_size_squares.push_back(std::vector<int>({formul / 2 + 1, formul + 1, formul / 2}));
    answer.coordinates_and_size_squares.push_back(std::vector<int>({formul + 1,formul + 1, formul / 2}));
    return answer;
}

//Функция, в который определяется случай решения и вызывается необходимая функция
void solution() {
    int size_square;
    std::cin >> size_square;
    if (size_square % 2 == 0){
        print_answer(even_size(size_square));
    }
    else if((size_square % 3 == 0) && (size_square > 3)){
        print_answer(multiple_of_three(size_square));
    }
    else{
        print_answer(find_splitting(size_square)); 
    }
}

//Головная функция
int main() {
    solution();
}