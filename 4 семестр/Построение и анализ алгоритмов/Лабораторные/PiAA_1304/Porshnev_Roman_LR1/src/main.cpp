#include <iostream>
#include <vector>
#include <cmath>


/* 
* Данная структура хранит текущую заполненность искомого квадрата в map,
* координаты точки (x, y), начиная с которой будет производится заливка,
* площадь текущего набора квадратов squareValue, размер текущего набора в numbOfSquares,
* информация о количестве квадратов размером от 1 до 4 в countEachSquareType
* размер предыдщуего поставленного квадрата в prevLength
*/
struct squareInfo {
	std::vector<std::vector<int>> map;
	int x;
	int y;
	int squareValue;
	int numbOfSquares;
	int countEachSquareType[5];
	int prevLength;
};


class Squares {
public:
	/*
	* Текущий рекорд количества квадратов хранится в minNumbOfSquares должен инициализироваться числом > 40^2 + 1
	* инициализация размера квадрата занчением n
	* инициализация "базового" квадрата размером baseN (т. е. максимальное уменьшение в масштабе квадрата размером n)
	* инициализация пустого квадрата bestMap с рамкой из -1, где будет храниться лучшая комбинация меньших квадратов
	*/
	Squares(int n, int baseN) {
		this->minNumbOfSquares = infinity;
		this->n = n;
		this->baseN = baseN;
		for (int i = 0; i < n + 2; i++) {
			std::vector<int> row;
			for (int j = 0; j < n + 2; j++) {
				if ((j == 0) or (j == n + 1)) {
					row.push_back(-1); // по бокам рамка из -1
				}
				else {
					row.push_back(0);
				}
			}
			bestMap.push_back(row);
		}
		for (int i = 1; i < n + 1; i++) { // Сверху рамка из -1
			bestMap[0][i] = -1;
		}
		for (int i = 1; i < n + 1; i++) {
			bestMap[n + 1][i] = -1; // Снизу рамка из -1
		}
	}

	/*Запуск заполнения искомого квадрата и вызов метода для вывода полученного ответа*/
	void Solution() {
		InitiateThreeStartSquares(); // заполнение 3-ёх квадратов
		PrintBestSet();
	}


private:
	/*Вывод полученного ответа на исходную задачу*/
	void PrintBestSet() {
		std::cout << minNumbOfSquares << std::endl;
		bool* visited = new bool[minNumbOfSquares + 1];
		for (int i = 0; i <= minNumbOfSquares; i++)
			visited[i] = false;

		for (int numb = 1; numb <= minNumbOfSquares; numb++) { // вывод набора квадратов
			int currentSquare = 0;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					if (bestMap[i][j] == numb) {
						if (!visited[bestMap[i][j]]) {
							visited[bestMap[i][j]] = true;
							std::cout << i << " " << j << " ";
						}
						currentSquare++;
					}
				}
			}
			std::cout << (int)sqrt(currentSquare) << "\n";
		}
	}

	/*
	Входные данные: структура с необходимыми данными состояния поля
	Данный метод представляет собой рекурсивный перебор с оптимизациями
	*/
	void FindMinNumbOfSquares(squareInfo sqInf) {
		if (sqInf.prevLength < 5) { // отсечение для квадратов размером до 5 на 5
			if (sqInf.prevLength % 2 == 1) { // для 1 и 3
				if (sqInf.countEachSquareType[sqInf.prevLength] > 5) {
					return;
				}
			}
			else {
				if (sqInf.countEachSquareType[sqInf.prevLength] > 4) { // для 2 и 4
					return;
				}
			}
		}

		if (sqInf.numbOfSquares >= minNumbOfSquares) // отсечение переполнения текущего минимума
			return;

		if (sqInf.squareValue == n * n) { // площадь текущего набора квадратов равна площади искомого квадрата
			if (sqInf.numbOfSquares < minNumbOfSquares) {
				minNumbOfSquares = sqInf.numbOfSquares; // запись нового рекорда
				bestMap = sqInf.map;
			}
			return;
		}

		while (sqInf.x <= n) {
			while (sqInf.y <= n) {
				if (sqInf.map[sqInf.x][sqInf.y] == 0) { // клетка свободна
					int maxLengthOfCurrentSquare = MaxLengthOfSquare(sqInf.map, sqInf.x, sqInf.y);
					// поиск максимального квадрата из данной клетки
					for (int length = maxLengthOfCurrentSquare; length > 0; length--) {
						// перебор всех возможных квадратов из данной клетки
						if (length == maxLengthOfCurrentSquare) {
							sqInf.map = FillingOfSquare(sqInf.map, sqInf.x, sqInf.y,
								length, sqInf.numbOfSquares + 1, filling); // заполнение
						}
						else {
							sqInf.map = FillingOfSquare(sqInf.map, sqInf.x + length, sqInf.y + length,
								length + 1, sqInf.numbOfSquares + 1, trimming);
							// урезание на 1

						}
						FindMinNumbOfSquares(GetInitiatedBlackoutSquareInfo(sqInf, length));
						// запуск рекурсии для следующей *возможно свбодной клетки
						// * - рекурсия может попасть сразу на правую границу столешницы
					}
					return;
				}
				sqInf.y++;
			}
			sqInf.x++;
			if (sqInf.x <= bigSquareLengthOfSide) {
				sqInf.y = bigSquareLengthOfSide + 1; // чтобы не попадать на заведомо заполненный большой квадрат
			}
			else {
				sqInf.y = n - bigSquareLengthOfSide + 1; // чтобы не попадать на заведомо на заполненный квадрат,
				// который меньше самого большого квадрата на минимальное количество клеток
			}
		}

	}

	/*
	* Вход: текущее состояние искомого квадрата map, координаты стартовой точки заливки (x, y)
	* Выход: максимальный размер квадрата, который можно вставить
	* Данный метод предназначен для поиска максимального квадрата, который можно вставить таким образом,
	* чтобы его левый верхний угол находился в точке с координатами (x, y)
	*/
	int MaxLengthOfSquare(std::vector<std::vector<int>> map, int x, int y) {
		int maxLengthOfSide = 0;
		while ((map[x][y + maxLengthOfSide] == 0) && (map[x + maxLengthOfSide][y] == 0)) {
			maxLengthOfSide++;
		}

		return maxLengthOfSide;
	}

	/*
	* Вход: состояние заполненности искомого квадрата map, 
	* координаты точки (x, y), начиная с которой будет производится заливка или урезание существующего квадрата,
	* длина стороны заполняемого или урезаемого квадрата lengthOfSide,
	* заливка или урезание - переменная direction
	* Выход: новое состояние заполненности искомого квадрата
	* Данный метод либо закрашивает новую область в виде квадрата, либо урезает уже существующую
	*/
	std::vector<std::vector<int>> FillingOfSquare(std::vector<std::vector<int>> map,
		int x, int y, int lengthOfSide, int color, int direction) {
		switch (direction)
		{
		case filling: // заполнение
			for (int i = x; i < x + lengthOfSide; i++)
				for (int j = y; j < y + lengthOfSide; j++)
					map[i][j] = color;
			break;
		case trimming: // урезание уже нарисованной области на 1
			for (int i = x; i > x - lengthOfSide; i--)
				map[i][y] = 0;
			for (int j = y; j > y - lengthOfSide; j--)
				map[x][j] = 0;
			break;
		}
		return map;
	}

	/*
	* Данный метод оптимально устанавливает первые 3 квадрата и запускает рекурсивный перебор
	*/
	void InitiateThreeStartSquares() {
		bigSquareLengthOfSide = (n / baseN) * ((baseN + 1) / 2);
		bestMap = FillingOfSquare(bestMap, 1, 1, bigSquareLengthOfSide, 1, filling); // нарисовать самый большой квадрат
		bestMap = FillingOfSquare(bestMap, 1, 1 + bigSquareLengthOfSide, n - bigSquareLengthOfSide, 2, filling); // нарисовать
		bestMap = FillingOfSquare(bestMap, 1 + bigSquareLengthOfSide, 1, n - bigSquareLengthOfSide, 3, filling); // 2 квадрата
		squareInfo sqInf;
		sqInf.map = bestMap;
		sqInf.x = n - bigSquareLengthOfSide + 1;
		sqInf.y = bigSquareLengthOfSide + 1;
		sqInf.squareValue = (int)pow(bigSquareLengthOfSide, 2) + 2 * (int)pow(n - bigSquareLengthOfSide, 2);
		sqInf.numbOfSquares = 3;
		for (int i = 0; i < 5; i++) {
			sqInf.countEachSquareType[i] = 0;
		};
		if (bigSquareLengthOfSide < 5) {
			sqInf.countEachSquareType[bigSquareLengthOfSide] = 1;
		}
		if (n - bigSquareLengthOfSide < 5) {
			sqInf.countEachSquareType[n - bigSquareLengthOfSide] = 2;
		}
		sqInf.prevLength = n - bigSquareLengthOfSide;
		FindMinNumbOfSquares(sqInf);
		// вызвать рисование остальных квадратов
	}

	/*
	* Вход: структура текущего состояния поля, сторона вставляемого квадрата 
	* Выход: обновлённая структура со вставленным квадратом
	* Данный метод обновляет текущее состояние поля после вставки в него квадрата размером length
	*/
	squareInfo GetInitiatedBlackoutSquareInfo(squareInfo sqInf, int length) {
		squareInfo sqInfBlack;
		sqInfBlack.map = sqInf.map;
		sqInfBlack.x = sqInf.x;
		sqInfBlack.y = sqInf.y + length;
		sqInfBlack.squareValue = sqInf.squareValue + (int)pow(length, 2);
		sqInfBlack.numbOfSquares = sqInf.numbOfSquares + 1;
		sqInfBlack.prevLength = length;
		for (int i = 0; i < 5; i++)
			sqInfBlack.countEachSquareType[i] = sqInf.countEachSquareType[i];
		if (length < 5) {
			sqInfBlack.countEachSquareType[length] = sqInfBlack.countEachSquareType[length] + 1;
		}

		return sqInfBlack;
	}


	int bigSquareLengthOfSide;
	std::vector<std::vector<int>> bestMap;
	int n;
	int baseN;
	int minNumbOfSquares;
	enum directions { filling = 1, trimming };
	int infinity = 10000;
};


class Factorization {
public:
	/*
	* Инициализация числа n, до которого будет производится поиск простых чисел
	* Инициализация первого простого числа p значением 2
	* Инициализация вектора чисел primeNumbers значениями true для последующего вычёркивания составных чисел
	*/
	Factorization(int n) {
		this->n = n;
		this->p = 2;
		for (int i = 0; i <= n; i++) {
			primeNumbers.push_back(true);
		}
	}

	/*
	* Данный метод представляет собой реализацию решета Эратосфена
	*/
	void Sieve() {
		while (p < n) {
			for (int i = 2 * p; i < n; i++) {
				if (i % p == 0) {
					primeNumbers[i] = false;
				}
			}
			if (p + 1 < n) {
				for (int i = p + 1; i <= n; i++) {
					if (primeNumbers[i] == true) {
						p = i;
						break;
					}
				}
			}
			else {
				p++;
			}
		}
	}

	/*
	* Выход: если n - составное число, то возвращается его минимальный простой делитель, иначе - само число n
	*/
	int IsComposite() { // cоставное ли число длина стороны n?
		for (int i = 2; i < n; i++) {
			if ((n % i == 0) && (primeNumbers[i] = true)) {
				return i; // n - cоставное
			}
		}
		return n; // n - простое
	}
private:
	int n;
	int p;
	std::vector<bool> primeNumbers;
};


int main() {
	int n;
	std::cin >> n;
	Factorization frz(n);
	frz.Sieve();
	Squares sqrs(n, frz.IsComposite());
	sqrs.Solution();
	return 0;
}
