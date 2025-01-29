#include <iostream>
#include <chrono>
#include <memory>

#include "ocl_matrices_multiplication.h"

int main()
{
	// Размер матриц
	size_t mat_n = 2048;

	auto start = std::chrono::high_resolution_clock::now();

	std::unique_ptr< int32_t[] > l_mat = std::make_unique< int32_t[] >(mat_n * mat_n);
	std::unique_ptr< int32_t[] > r_mat = std::make_unique< int32_t[] >(mat_n * mat_n);

	// Заполнение матриц
	for (size_t i = 0; i < mat_n * mat_n; i++) 
	{
		l_mat[i] = i % 32;
		r_mat[i] = i % 32;
	}

	// Умножение
	ocl::OclMatricesMultiplication mult;
	mult.init(mat_n, mat_n, mat_n, l_mat.get(), r_mat.get());
	std::unique_ptr< int32_t[] > result = mult.process();
	mult.deinit();

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Время: " 
		<< std::chrono::duration_cast< std::chrono::milliseconds >(end - start).count() 
		<< std::endl;

	// // Вывод
	// for (size_t y = 0; y < mat_n; y++)
	// {
	// 	for (size_t x = 0; x < mat_n; x++)
	// 	{
	// 		std::cout << result[x + y * mat_n] << " ";
	// 	}
	// 	std::cout << "\n";
	// }

	return 0;
}
