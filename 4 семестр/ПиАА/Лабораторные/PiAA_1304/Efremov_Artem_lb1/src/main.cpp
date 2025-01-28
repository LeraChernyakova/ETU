#include <iostream>
#include <vector>
#include <cmath>

//Статическая переменная, описывающая размер столешницы
static int N;
//Статическая переменная, описывающая минимальное количество квадратов, необходимых для столешницы
static int square_counter;

//Класс, описывающий квадрат
//Содержит три поля типа int - координаты левого верхнего угла и размер стороны квадрата
class Square{
public:
	int x;											
	int y;											
	int w;			
	//Конструктор класса
	Square(int x, int y, int w);
};

//Описание констурктора класса Square, заполнение полей аргументами
Square::Square(int x, int y, int w) {
	this->x = x;
	this->y = y;
	this->w = w;
}

//Статическая переменная, описывающая финальный минимальный набор квадратов необходимый для столешницы
static std::vector<Square> final_array;

//Проверка на наложение нового квадрата на уже существующий
//Принимает вектор уже существующих квадратов и координаты нового
//Возвращает значение true-false в зависимости от положительного или отрицательного результата проверки
bool overlay_check(std::vector<Square> board, int x, int y) {
	for (auto square : board) {
		if (x >= square.x && x < square.x + square.w && y >= square.y && y < square.y + square.w) {
			return false;
		}
	}
	return true;
}

//Реализация алгоритма поиска с возвратом, рекурсивный метод
//Принимает вектор уже расположенных квадратов, значение покрытой квадратами площади, количество квадратов, минимальные возможные координаты нового квадрата
//Итогом работы является заполненный вектор минимального набора квадратов
void backtracking(std::vector<Square> board, int square_sum, int square_amount, int minx, int miny) {
	for (int x = minx; x < N; x++) {
		for (int y = miny; y < N; y++) {
			if (overlay_check(board, x, y)) {				
				int new_square_width = fmin(N - x, N - y);
				for (auto square : board) {
					if (square.x + square.w > x and square.y > y) {
						new_square_width = fmin(new_square_width, square.y - y);
					}
				}
				for (int i = new_square_width; i > 0; i--) {
					Square sq(x, y, i);
					std::vector<Square> board_copy;
					std::copy(board.begin(), board.end(), back_inserter(board_copy));
					board_copy.push_back(sq);
					if (square_sum + pow(sq.w, 2) == pow(N, 2)) {		
						if (square_amount + 1 < square_counter) {
							square_counter = square_amount + 1; 
							final_array.clear();
							std::copy(board_copy.begin(), board_copy.end(), back_inserter(final_array));
						}
					}
					else {
						if (square_amount + 1 < square_counter) {
							backtracking(board_copy, square_sum + pow(sq.w, 2), square_amount + 1, x, y + i);
						}
						else {
							return;
						}	
					}
				}
				return;
			}
		}
		miny = N / 2;
	}
}

//Функция вывода ответа на консоль
//Принимает масштаб квадратов (размер стороны)
void printing(int boardsize) {
	std::cout << final_array.size() << std::endl;
	for (auto i : final_array) {
		std::cout << i.x * boardsize << " " << i.y * boardsize << " " << i.w * boardsize << std::endl;
	}	
}

//Заполнение вектора тремя начальными квадратами
//Принимает вектор уже заполненных квадратов
void filling_basic_squares(std::vector<Square> &board) {
	Square s1(0, 0, (N + 1) / 2);
	board.push_back(s1);
	Square s2(0, (N + 1) / 2, N / 2);
	board.push_back(s2);
	Square s3((N + 1) / 2, 0, N / 2);
	board.push_back(s3);
}

//Масштабирование столешницы
//Принимает ссылку на размер стороны квадрата (масштаб квадрата)
//Итогом работы является вычисленный масштаб стороны квадрата и размер столешницы
void scaling(int &boardsize) {
	for (int i = 1; i < N; i++) {
		if (N % i == 0) {
			boardsize = i;
		}
	}
	N /= boardsize;
}

//Решение задачи
//Инициализация основных переменных и вызывов функций
void solution() {
	std::cin >> N;

	square_counter = 2 * N + 1;
	int boardsize = 0;
	std::vector<Square> board;

	scaling(boardsize);
	filling_basic_squares(board);
	backtracking(board, pow((N + 1) / 2, 2) + 2 * pow(N / 2, 2), 3, N / 2, (N + 1) / 2);
	printing(boardsize);
}

//Главная функция
int main() {
	solution();
	return 0;
}