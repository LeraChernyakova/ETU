#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <chrono>
#include <climits>
#define OPTIMAL_MAX_AMOUNT_OF_SQUARES 13


struct vec3d;
int bestCounter = INT_MAX;
std::vector<std::vector<int>> bestMap;
std::vector<vec3d> bestVec;


void printVec3D(vec3d dummyVec);
void printAnswer(std::vector<vec3d> outputVec, int amountOfColors);
vec3d makeVec3D(int x, int y, int w);
std::vector<vec3d> getBestVtx(std::vector<std::vector<int>>& map, int mapSize, int amountOfColors);
std::vector<vec3d> getBestVtxEven(int mapSize);
void makeBestVtxDivisableByThree(int mapSize);
bool tryToPutSquare(int row, int col, int sizeOfSquareToPut, std::vector<std::vector<int>>& map, int mapSize);
void putSquare(int row, int col, int sizeOfSquareToPut, std::vector<std::vector<int>>& map, int mapSize, int colorCounter);
void divide(int mapSize, std::vector<std::vector<int>>& map, int freeArea, int colorCounter);
std::vector<std::vector<int>> getCleanMap(int sizeOfMap);
void getOptimalStartForPrimes(std::vector<std::vector<int>>& map, int sizeOfMap, int& colorCounter, int& freeArea);
void getSolutionForEven(int mapSize);
void getSolution();
void readMapSize(int& mapSize);

int main() {
	getSolution();
	return 0;
}

//Содержит три поля типа int
struct vec3d {
	int x;
	int y;
	int w;
};
//Выводит vec3d в консоль
void printVec3D(vec3d dummyVec) {
	std::cout << dummyVec.x << " " << dummyVec.y << " " << dummyVec.w << '\n';
}
//Выводит ответ в требуемом в задаче формате в консоль
void printAnswer(std::vector<vec3d> outputVec, int amountOfColors) {
	std::cout << amountOfColors << std::endl;
	for (int i = 0; i < outputVec.size(); i++) {
		printVec3D(outputVec[i]);
	}
}
//Создаёт и возвращает структуру vec3d по трём целочисленным значениям 
vec3d makeVec3D(int x, int y, int w) {
	vec3d vecToReturn;
	vecToReturn.x = x;
	vecToReturn.y = y;
	vecToReturn.w = w;
	return vecToReturn;
}
//Создаёт и возвращает вектор vec3d, содержащий ответ в требуемом в задаче формате по карте, её размеру и числу квадратов в разбиении. 
std::vector<vec3d> getBestVtx(std::vector<std::vector<int>>& map, int mapSize, int amountOfColors) {
	std::vector<vec3d> vecToReturn;
	std::vector<int> colorCounterArr(20, 0);
	int curColor = 0;
	std::vector<int>::iterator it;
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			if (colorCounterArr[map[i][j]] == 0) {
				vecToReturn.push_back(makeVec3D(i, j, map[i][j]));
				curColor = map[i][j];
			}
			colorCounterArr[map[i][j]]++;
		}
	}

	for (int i = 0; i < vecToReturn.size(); i++) {
		vecToReturn[i].x++;
		vecToReturn[i].y++;
		vecToReturn[i].w = (int)sqrt(colorCounterArr[vecToReturn[i].w]);
	}
	return vecToReturn;
}
//Создаёт и возвращает вектор vec3d, содержащий ответ в требуемом в задаче формате для чётных по размеру карты
std::vector<vec3d> getBestVtxEven(int mapSize) {
	int numForDisecting = mapSize / 2;
	std::vector<vec3d> vecToReturn;
	vecToReturn.push_back(makeVec3D(0 + 1, 0 + 1, numForDisecting));
	vecToReturn.push_back(makeVec3D(0 + 1, numForDisecting + 1, numForDisecting));
	vecToReturn.push_back(makeVec3D(numForDisecting + 1, 0 + 1, numForDisecting));
	vecToReturn.push_back(makeVec3D(numForDisecting + 1, numForDisecting + 1, numForDisecting));
	return vecToReturn;
}

//Выводит ответ в консоль, в заданном в задаче формате для кратных трём. На вход - 
void makeBestVtxDivisableByThree(int mapSize) {
	int scale = mapSize / 3;
	std::vector<vec3d> vecToReturn;
	int smallerSolutionForScale = 3;
	auto map = getCleanMap(smallerSolutionForScale);
	int freeArea = smallerSolutionForScale * smallerSolutionForScale;
	int colorCounter = 1;
	getOptimalStartForPrimes(map, smallerSolutionForScale, colorCounter, freeArea);
	divide(smallerSolutionForScale, map, freeArea, colorCounter);
	for (auto& vec : bestVec) {
		vec.x = (vec.x - 1) * scale + 1;
		vec.y = (vec.y - 1) * scale + 1;
		vec.w = (vec.w) * scale;
	}
	printAnswer(bestVec, bestCounter);
}




/*Пробует поставить квадрат в заданную клетку на карте. Возвращает true если удалось, false - если не удалось.
На вход - челочисленные координаты row, col, размер квадрата для вставки, карта и её размер*/
bool tryToPutSquare(int row, int col, int sizeOfSquareToPut, std::vector<std::vector<int>>& map, int mapSize) {
	if ((row + sizeOfSquareToPut > mapSize) || (col + sizeOfSquareToPut > mapSize)) {
		return false;
	}
	for (int i = row; i < sizeOfSquareToPut + row; i++) {
		if ((map[i][col] != 0) || (map[i][col + sizeOfSquareToPut - 1] != 0)) {
			return false;
		}
	}
	for (int j = col; j < sizeOfSquareToPut + col; j++) {
		if ((map[row][j] != 0) || (map[row + sizeOfSquareToPut - 1][j] != 0)) {
			return false;
		}
	}
	return true;
}

/*Ставит квадрат в заданную клетку на карте. На вход - челочисленные координаты row, col, размер квадрата для вставки, карта и её размер, счётчик количества квадратов*/
void putSquare(int row, int col, int sizeOfSquareToPut, std::vector<std::vector<int>>& map, int mapSize, int colorCounter) {
	for (int i = row; i < sizeOfSquareToPut + row; i++) {
		for (int j = col; j < sizeOfSquareToPut + col; j++) {
			map[i][j] = colorCounter;
		}
	}
}
//Рекурсивная функция, перебирает возможные разбиения. На вход - размер карты, карта, свободная на карте площадь, счётчик квадратов
void divide(int mapSize, std::vector<std::vector<int>>& map, int freeArea, int colorCounter) {
	if (colorCounter >= bestCounter || colorCounter > OPTIMAL_MAX_AMOUNT_OF_SQUARES) {
		return;
	}
	for (int i = (mapSize + 1) / 2 - 1; i < mapSize; i++) {
		for (int j = (mapSize + 1) / 2 - 1; j < mapSize; j++) {
			for (int sizeOfInputSquare = mapSize - (mapSize + 1) / 2; sizeOfInputSquare >= 1; sizeOfInputSquare--) {
				if (tryToPutSquare(i, j, sizeOfInputSquare, map, mapSize)) {
					auto newMap = map;
					putSquare(i, j, sizeOfInputSquare, newMap, mapSize, colorCounter);
					if ((freeArea - sizeOfInputSquare * sizeOfInputSquare) > 0) {
						divide(mapSize, newMap, freeArea - sizeOfInputSquare * sizeOfInputSquare, colorCounter + 1);
					}
					else {
						if (colorCounter < bestCounter) {
							bestMap = newMap;
							bestCounter = colorCounter;
							bestVec = getBestVtx(newMap, mapSize, bestCounter);
						}
						return;
					}
					if (sizeOfInputSquare == 1) {
						return;
					}
				}
			}
		}
	}
}
//Создаёт и возвращает чистую карту заданного размера (вектор векторов целочисленных значений) по размеру на входе
std::vector<std::vector<int>> getCleanMap(int sizeOfMap) {
	std::vector<std::vector<int>> map;
	std::vector<int> tmp(sizeOfMap, 0);
	for (int i = 0; i < sizeOfMap; i++) {
		map.push_back(tmp);
	}
	return map;
}
/*Заполняет чистую карту тремя квадратами, сокращающими количество вариантов, которых надо перебирать
На вход - карта, её размер, счётчик квадратов и свободная площадь*/
void getOptimalStartForPrimes(std::vector<std::vector<int>>& map, int sizeOfMap, int& colorCounter, int& freeArea) {
	int sizeOfSquareOne = (sizeOfMap + 1) / 2;
	int sizeOfSquareTwo = sizeOfMap - sizeOfSquareOne;
	putSquare(0, 0, sizeOfSquareOne, map, sizeOfMap, colorCounter++);
	putSquare(sizeOfSquareOne, 0, sizeOfSquareTwo, map, sizeOfMap, colorCounter++);
	putSquare(0, sizeOfSquareOne, sizeOfSquareTwo, map, sizeOfMap, colorCounter++);
	freeArea -= sizeOfSquareOne * sizeOfSquareOne + 2 * sizeOfSquareTwo * sizeOfSquareTwo;
}
//Вспомогательная для getSolution функция (выводит ответ в консоль по размеру карты для квадратов с чётной стороной)
void getSolutionForEven(int mapSize) {
	auto bestVec = getBestVtxEven(mapSize);
	printAnswer(bestVec, 4);
}
//Запускает решение задачи
void getSolution() {
	int mapSize;
	readMapSize(mapSize);
	if (mapSize % 2 == 0) {
		getSolutionForEven(mapSize);
	}
	else if (mapSize % 3 == 0) {
		makeBestVtxDivisableByThree(mapSize);
	}
	else {
		auto map = getCleanMap(mapSize);
		int freeArea = mapSize * mapSize;
		int colorCounter = 1;
		getOptimalStartForPrimes(map, mapSize, colorCounter, freeArea);
		divide(mapSize, map, freeArea, colorCounter);
		printAnswer(bestVec, bestCounter);
	}
}
//Считывает размер карты (получает на вход целочисленное значение по адресу)
void readMapSize(int& mapSize) {
	std::cin >> mapSize;
}