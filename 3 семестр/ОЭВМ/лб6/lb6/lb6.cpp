#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <stdio.h> 
#include <fstream> 
#include <string> 
#include <random> 
#include "Randomer.h" 
#include <locale> 

extern "C" void first(int* numbers, int n, int* result1, int x_min);
extern "C" void second(int* result1, int* intervals, int* result2, int x_max, int x_min, int n_int);


int main(){
	setlocale(LC_ALL, "Russian");
	int n, x_min, x_max, r_last, n_int;
	std::cout << "Введите длину массива" << std::endl;
	std::cin >> n;
	if (n <= 0 || n > 16384) {//проверка на корретный ввод массива 
		std::cout << "0 < n <= 16384!!" << std::endl;
		return 0;
	}
	std::cout << "Введите Xmin" << std::endl;
	std::cin >> x_min;
	std::cout << "Введите Xmax" << std::endl;
	std::cin >> x_max;
	if (x_max <= x_min) {
		std::cout << "Xmax > Xmin!" << std::endl;
		return 0;
	}

	std::cout << "Введите количество интервалов" << std::endl;
	std::cin >> n_int;
	int Dx = x_max - x_min;
	if (n_int <= 0 || n_int > 24 || n_int < Dx) {
		std::cout << "0 < n_int <= 24 и n_int > Dx, где Dx = Xmax - X min = " << x_max << " - " << x_min << " = " << Dx << std::endl;
		system("Pause");
		return 0;
	}

	int cnt_lg = 0;
	int* intervals = new int[n_int+1];
	for (int i = 0; i < n_int; i++) {
		std::cout << "Введите левую границу " << i << " интервала" << std::endl;
		std::cin >> intervals[i];
		if (intervals[i] <= x_min) {
			cnt_lg++;
		}
	}

	if (cnt_lg == 0) {
		std::cout << "Ни одна левая граница не удовлетворяет условию: Lgi <= Xmin !" << std::endl;
		return 0;
	}

	std::cout << "Введите правую границу последнего интервала" << std::endl;
	std::cin >> r_last;

	if (r_last <= x_max) {
		std::cout << "Не выполнено условие Rg > Xmax" << std::endl;
		return 0;
	}

	intervals[n_int] = r_last;

	for (int i = 0; i < n_int+1; i++) {
		for (int j = i; j < n_int+1; j++) {
			if (intervals[i] > intervals[j]) {
				std::swap(intervals[i], intervals[j]);
			}
		}
	}

	for (int i = 0; i < n_int; i++) {
		std::cout << intervals[i] << " ";
	}
	std::cout << std::endl;

	int* numbers = new int[n];
	dnk_randomize();//начальная иницализация 
	for (int i = 0; i < n; i++) {
		numbers[i] = (int)round(dnk_normal((x_max + x_min) / 2.0, (x_max - x_min) / 3.0));//вычисление рандомного числа 
		if (numbers[i] > x_max || numbers[i] < x_min)
			i--;
		else
			std::cout << numbers[i] << " ";
	}
	std::cout << std::endl;


	int* result1 = new int[abs(x_max - x_min) + 1];
	int* result2 = new int[n_int];
	for (int i = 0; i < abs(x_max - x_min) + 1; i++) {
		result1[i] = 0;
	}
	for (int i = 0; i < n_int; i++) {
		result2[i] = 0;
	}
	first(numbers, n, result1, x_min);
	//for (int i = 0; i < n; i++)
		//printf("%d ", numbers[i]);
	for (int i = 0; i < abs(x_max - x_min); i++) {
		std::cout << i + x_min << ": " << result1[i] << " | ";
	}
	std::cout << std::to_string(abs(x_max - x_min) + x_min) << ": " << result1[abs(x_max - x_min)] << std::endl;
	second(result1, intervals, result2, x_max, x_min, n_int);

	std::ofstream file("table.txt");
	auto head = "n_int\tLg\tvalue";
	file << head << std::endl;
	std::cout << head << std::endl;
	for (int i = 0; i < n_int; i++) {
		auto line = std::to_string(i) + "\t" + std::to_string(intervals[i]) + "\t" + std::to_string(result2[i]) + "\n";
		file << line;
		std::cout << line;
	}
	return 0;
}
