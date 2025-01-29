#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

using xy = std::pair<double, double>;

double f(double x)
{
	return std::sin((M_PI * x) / 2.0);
}

double lagrange_polynom(double x, const std::vector<xy>& data);
double newton_polynom_forward(double x, const std::vector<xy>& data, double** differences);
double newton_polynom_backward(double x, const std::vector<xy>& data, double** differences);
double approximation(double x, std::pair<double, double> approx_coeffs);

std::pair<double, double> approx_coeffs(const std::vector<xy>& data);
double lagrange_multiplier(double x, const std::vector<xy>& data, int i);
double** calc_finite_differences(const std::vector<xy>& data);
void calc_n_differences(double** differences, int order, int count);

void print_lagrange_polynom(const std::vector<xy>& data);
void print_newton_polynom_forward(const std::vector<xy>& data, double** differences);
void print_newton_polynom_backward(const std::vector<xy>& data, double** differences);
void print_approximation(std::pair<double, double> approx_coeffs);
std::pair<int64_t, int64_t> sc_numbers(double calculated, double exact);

int main()
{
	std::vector<xy> data;
	data.push_back({-1.0, -1.00});
	data.push_back({-0.6, -0.81});
	data.push_back({-0.2, -0.31});
	data.push_back({0.2, 0.31});
	data.push_back({0.6, 0.81});
	data.push_back({1.0, 1.00});

	double** differences = calc_finite_differences(data);
	std::pair<double, double> approximation_coeffs = approx_coeffs(data);

	std::vector<double> x({-0.72, 0.13, 0.68});
	double exact;
	double result;
	double abs_inaccuracy;
	double rel_inaccuracy;
	std::pair<int64_t, int64_t> sc;

	for (size_t i = 0; i < x.size(); ++i)
	{
		exact = f(x[i]);
		std::printf("|%-19s|%8s|%12s|%23s|%10s|%10s|%21s|%12s|\n", "Метод", "X", "Знач в точке", "Вычисленное", "Абс погреш", "Отн погреш", "Знач цифры", "Верные цифры");
		std::printf("-----------------------------------------------------------------------------------------------------\n");
		
		result = lagrange_polynom(x[i], data);
		abs_inaccuracy = std::fabs(exact - result);
		rel_inaccuracy = std::fabs(abs_inaccuracy / exact);
		sc = sc_numbers(result, exact);

		std::printf("|%-21s|%8.4f|%12.8lf|%12.8lf|%10.8lf|%10.8lf|%12ld|%12ld|\n",
			"Лагранж",
			x[i],
			exact,
			result,
			abs_inaccuracy,
			rel_inaccuracy,
			sc.first,
			sc.second
		);

		result = newton_polynom_forward(x[i], data, differences);
		abs_inaccuracy = std::fabs(exact - result);
		rel_inaccuracy = std::fabs(abs_inaccuracy / exact);
		sc = sc_numbers(result, exact);

		std::printf("|%-21s|%8.4f|%12.8lf|%12.8lf|%10.8lf|%10.8lf|%12ld|%12ld|\n",
			"Форвард",
 			x[i],
			exact,
			result,
			abs_inaccuracy,
			rel_inaccuracy,
			sc.first,
			sc.second
		);

		result = newton_polynom_backward(x[i], data, differences);
		abs_inaccuracy = std::fabs(exact - result);
		rel_inaccuracy = std::fabs(abs_inaccuracy / exact);
		sc = sc_numbers(result, exact);

		std::printf("|%-16s|%8.4f|%12.8lf|%12.8lf|%10.8lf|%10.8lf|%12ld|%12ld|\n",
			"Ньютон обр ход",
			x[i],
			exact,
			result,
			abs_inaccuracy,
			rel_inaccuracy,
			sc.first,
			sc.second
		);

		result = approximation(x[i], approximation_coeffs);
		abs_inaccuracy = std::fabs(exact - result);
		rel_inaccuracy = std::fabs(abs_inaccuracy / exact);
		sc = sc_numbers(result, exact);

		std::printf("|%-27s|%8.4f|%12.8lf|%12.8lf|%10.8lf|%10.8lf|%12ld|%12ld|\n",
			"Аппроксимация",
			x[i],
			exact,
			result,
			abs_inaccuracy,
			rel_inaccuracy,
			sc.first,
			sc.second
		);
		std::printf("-----------------------------------------------------------------------------------------------------\n");
	}

	/* pt. 6 */
	std::vector<xy> data_br;
	data_br.push_back({-1.0, -1.00});
	data_br.push_back({-0.6, -0.81});
	data_br.push_back({-0.2, -0.31 * 1.5});
	data_br.push_back({0.2, 0.31});
	data_br.push_back({0.6, 0.81});
	data_br.push_back({1.0, 1.00});
	double** differences_br = calc_finite_differences(data_br);
	std::printf("\nКонечная разность без погрешности\n");
	std::printf("|%8s|%8s|%9s|%9s|\n", "X", "Y", "Δy", "Δ^2y");
	std::printf("-------------------------------------\n");
	for (int i = 0; i < data.size(); ++i)
	{
		if (data.size() - i > 2)
			std::printf("|%8.5g|%8.5g|%8.5g|%8.5g|\n", data.at(i).first, differences[0][i], differences[1][i], differences[2][i]);
		else if (data.size() - i == 1)
			std::printf("|%8.5g|%8.5g|%8s|%8s|\n", data.at(i).first, differences[0][i], "-", "-");
		else
			std::printf("|%8.5g|%8.5g|%8.5g|%8s|\n", data.at(i).first, differences[0][i], differences[1][i], "-");
	}
	std::printf("-------------------------------------\n");
	std::printf("\nКонечная разность с погрешностью\n");
	std::printf("|%8s|%8s|%9s|%9s|\n", "X", "Y", "Δy", "Δ^2y");
	std::printf("-------------------------------------\n");
	for (int i = 0; i < data_br.size(); ++i)
	{
		if (data_br.size() - i > 2)
			std::printf("|%8.5g|%8.5g|%8.5g|%8.5g|\n", data_br.at(i).first, differences_br[0][i], differences_br[1][i], differences_br[2][i]);
		else if (data_br.size() - i == 1)
			std::printf("|%8.5g|%8.5g|%8s|%8s|\n", data_br.at(i).first, differences_br[0][i], "-", "-");
		else
			std::printf("|%8.5g|%8.5g|%8.5g|%8s|\n", data_br.at(i).first, differences_br[0][i], differences_br[1][i], "-");
	}
	std::printf("-------------------------------------\n");
	

	std::printf("\n|%-21s|%8s|%12s|%23s|%10s|%10s|%21s|%12s|\n", "Метод", "X", "Знач в точке", "Вычисленное", "Абс погреш", "Отн погреш", "Знач цифры", "Верные цифры");
	std::printf("-----------------------------------------------------------------------------------------------------\n");
	std::printf("|%-28s|%8s|%12s|%12s|%10s|%10s|%12s|%12s|\n", "Интерполяция", "", "", "", "", "", "", "");
	for (int i = 0; i < x.size(); ++i)
	{
		exact = f(x[i]);
		result = lagrange_polynom(x[i], data);
		abs_inaccuracy = std::fabs(exact - result);
		rel_inaccuracy = std::fabs(abs_inaccuracy / exact);
		sc = sc_numbers(result, exact);

		std::printf("|%-16s|%8.4f|%12.8lf|%12.8lf|%10.8lf|%10.8lf|%12ld|%12ld|\n",
			"",
			x[i],
			exact,
			result,
			abs_inaccuracy,
			rel_inaccuracy,
			sc.first,
			sc.second
		);
	}
	std::printf("-----------------------------------------------------------------------------------------------------\n");

	std::printf("\n|%-21s|%8s|%12s|%23s|%10s|%10s|%21s|%12s|\n", "Метод", "X", "Знач в точке", "Вычисленное", "Абс погреш", "Отн погреш", "Знач цифры", "Верные цифры");
	std::printf("-----------------------------------------------------------------------------------------------------\n");
	std::printf("|%-29s|%8s|%12s|%12s|%10s|%10s|%12s|%12s|\n", "Аппроксимация", "", "", "", "", "", "", "");
	for (int i = 0; i < x.size(); ++i)
	{
		exact = f(x[i]);
		result = approximation(x[i], approximation_coeffs);
		abs_inaccuracy = std::fabs(exact - result);
		rel_inaccuracy = std::fabs(abs_inaccuracy / exact);
		sc = sc_numbers(result, exact);

		std::printf("|%-16s|%8.4f|%12.8lf|%12.8lf|%10.8lf|%10.8lf|%12ld|%12ld|\n",
			"",
			x[i],
			exact,
			result,
			abs_inaccuracy,
			rel_inaccuracy,
			sc.first,
			sc.second
		);
	}
	std::printf("-----------------------------------------------------------------------------------------------------\n");

	std::cout << std::endl;
	print_lagrange_polynom(data);
	print_newton_polynom_forward(data, differences);
	print_newton_polynom_backward(data, differences);
	print_approximation(approximation_coeffs);

	for (int i = 0; i < data.size(); ++i)
	{
		delete [] differences_br[i];
		delete [] differences[i];
	}
	delete [] differences_br;
	delete [] differences;
	
	return 0;
}

double lagrange_polynom(double x, const std::vector<xy>& data)
{
	double result = 0;
	for (int i = 0; i < data.size(); ++i)
		result += data[i].second * lagrange_multiplier(x, data, i);
	return result;
}

double lagrange_multiplier(double x, const std::vector<xy>& data, int i)
{
	double multiplier = 1;
	for (int k = 0; k < data.size(); ++k)
	{
		if (k == i)
			continue;
		multiplier *= (x - data[k].first) / (data[i].first - data[k].first);
	}
	return multiplier;
}

double** calc_finite_differences(const std::vector<xy>& data)
{
	double** differences = new double*[data.size()];
	for (int i = 0; i < data.size(); ++i)
		differences[i] = new double[data.size()];

	for (int i = 0; i < data.size(); ++i)
		differences[0][i] = data[i].second;

	for (int i = 1; i < data.size(); ++i)
		calc_n_differences(differences, i, data.size() - i);

	return differences;
}

void calc_n_differences(double** differences, int order, int count)
{
	for (int i = 0; i < count; ++i)
		differences[order][i] = differences[order - 1][i + 1] - differences[order - 1][i];
}

double newton_polynom_forward(double x, const std::vector<xy>& data, double** differences)
{
	double result = data.at(0).second;
	double denom = 1;
	double multiplier = 1;
	double h = data.at(1).first - data.at(0).first;
	for (int i = 1; i < data.size(); ++i)
	{
		denom *= i * h;
		multiplier *= x - data.at(i - 1).first;
		result += differences[i][0] * multiplier / denom;
	}
	return result;
}

double newton_polynom_backward(double x, const std::vector<xy>& data, double** differences)
{
	double result = data.at(data.size()-1).second;

	double denom = 1;
	double multiplier = 1;
	double h = data.at(1).first - data.at(0).first;
	for (int i = data.size() - 2; i >= 0; --i)
	{
		denom *= (data.size() - i - 1) * h;
		multiplier *= x - data.at(i + 1).first;
		result += differences[data.size() - i - 1][i] * multiplier / denom;
	}
	return result;
}

std::pair<double, double> approx_coeffs(const std::vector<xy>& data)
{
	double x_sum = 0, x2_sum = 0, y_sum = 0, xy_sum = 0;
	int n = data.size();
	for (const xy& element: data)
	{
		x_sum += element.first;
		y_sum += element.second;
		xy_sum += element.first * element.second;
		x2_sum += element.first * element.first;
	}
	double a = (n * xy_sum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum);
	double b = (y_sum - a * x_sum) / n;
	return {a, b};
}

double approximation(double x, std::pair<double, double> approx_coeffs)
{
	return approx_coeffs.first * x + approx_coeffs.second;
}

std::pair<int64_t, int64_t> sc_numbers(double calculated, double exact)
{
	int64_t significant, correct;
	int64_t signs = 8, correct_cnt = 0;
	double inaccuracy = std::fabs(exact - calculated);
	int64_t nums_cnt;
	for (int64_t i = 0; i < signs; ++i)
	{
		if (correct_cnt == 0 && inaccuracy < 1)
			inaccuracy *= 10;
		else if (correct_cnt == 0)
			correct_cnt = i;
		calculated *= 10;
		exact *= 10;
	}
	significant = static_cast<int64_t>(std::fabs(calculated));
	correct = static_cast<int64_t>(std::fabs(exact));
	nums_cnt = std::to_string(significant).size();
	correct = significant / std::pow(10, 1 + nums_cnt - correct_cnt);
	return {significant, correct};
}


void print_lagrange_polynom(const std::vector<xy>& data)
{
	double result = 0;
	std::cout << "Полином Лагранжа" << std::endl;
	std::cout << "f(x) = 0";
	for (int i = 0; i < data.size(); ++i)
	{
		std::cout << " + (" << data[i].second << ")" << "";
		double denom = 1;
		for (int k = 0; k < data.size(); ++k)
		{
			if (k == i)
				continue;
			denom *= (data[i].first - data[k].first);
		}
		std::cout << "(" << denom << ")";
		for (int k = 0; k < data.size(); ++k)
		{
			if (k == i)
				continue;
			std::cout << "(x - " << data[k].first << ")";
			denom *= (data[i].first - data[k].first);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void print_newton_polynom_forward(const std::vector<xy>& data, double** differences)
{
	double denom = 1;
	double h = data.at(1).first - data.at(0).first;
	std::cout << "Полином Ньютона прямой ход" << std::endl;
	std::cout << data.at(0).second;
	for (int i = 1; i < data.size(); ++i)
	{
		std::cout << " + ";
		denom *= i * h;
		std::cout << "(" << differences[i][0] << "/" << denom << ")"; 
		for (int k = 1; k <= i; ++k)
			std::cout << "(x - " << data.at(k - 1).first << ")";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void print_newton_polynom_backward(const std::vector<xy>& data, double** differences)
{
	double denom = 1;
	double h = data.at(1).first - data.at(0).first;
	std::cout << "Полином Ньютона обратный ход" << std::endl;
	std::cout << data.at(data.size()-1).second;
	for (int i = data.size() - 2; i >= 0; --i)
	{
		std::cout << " + ";
		denom *= (data.size() - i - 1) * h;
		std::cout << "(" << differences[i][0] << "/" << denom << ")"; 
		for (int k = data.size() - 2; k >= i; --k)
			std::cout << "(x - " << data.at(k + 1).first << ")";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void print_approximation(std::pair<double, double> approx_coeffs)
{
	std::cout << "Аппроксимация" << std::endl;
	std::cout << approx_coeffs.first << "x + " << approx_coeffs.second << std::endl;
	std::cout << std::endl;
}

