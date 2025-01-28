#include <iostream>
#include <string>
#include <vector>

#define pattern_not_in_text -1
#define index_not_find -1

// Функция, вычисляющая вспомогательную префиксную функцию
// заданного образца для работы алгоритма Кнута-Морриса-Пратта
// Принимает на вход строку, для которой необходимо вычислить функцию
// Возвращает вектор - значение префиксной функции
std::vector<int> computePrefixFunction(std::string pattern) {
    int pattern_length = pattern.size();
    std::vector<int>  prefix_function(pattern_length,0);
    int prefix_value = 0;
    for (int i  = 1; i < pattern_length; i++) {
        // если веил функция больше нуля и згначения не сопъвпали - переход к предыдущему
        while (prefix_value > 0 && pattern[prefix_value] != pattern[i]) {
            prefix_value = prefix_function[prefix_value-1];
        }  
        if (pattern[prefix_value] == pattern[i]) {
            prefix_value += 1;
        }
        prefix_function[i] = prefix_value;
    }
    return prefix_function;
}

// Функция, реализующая алгоритм Кнута-Морриса-Пратта
// для нахождения всех вхождений шаблона в текст
// Принимает на вход текст и шаблон
// Возвращает вектор, хранящий индексы начала вхождений шаблона в текст
std::vector<int> findOccurrenceInTextKMP(std::string text, std::string pattern) {
    int text_length = text.size();
    int pattern_length = pattern.size();
    std::vector<int> index_inclusion;
    std::vector<int> prefix_function_pattern = computePrefixFunction(pattern);
    int count_equal_symbols = 0;
    for (int i = 0; i < text_length; i++) {
        while (count_equal_symbols > 0 && pattern[count_equal_symbols] != text[i]) {
            count_equal_symbols = prefix_function_pattern[count_equal_symbols-1];
        }
        if (pattern[count_equal_symbols] == text[i]) {
            count_equal_symbols = count_equal_symbols + 1;
        }
        if (count_equal_symbols == pattern_length) {
            index_inclusion.push_back(i - pattern_length + 1);
            count_equal_symbols = prefix_function_pattern[count_equal_symbols-1];
        }
            
    }
    return index_inclusion;
}

// Функция, реализующая алгоритм Кнута-Морриса-Пратта для определения,
// является ли первая строка циклическим сдвигом второй строки
// Принимает на вход две строки
// Возвращает значение - индекс начала второй строки в первой
int checkCycleShiftKMP(std::string first_string, std::string second_string) {
    int index_cycle_shift = index_not_find;
    int first_string_length = first_string.size();
    int second_string_length = second_string.size();
    if (first_string_length == second_string_length) {
        std::string first_string_modify= first_string + first_string;
        int first_string_modify_length = first_string_modify.size();
        std::vector <int> prefix_function_second_string = computePrefixFunction(second_string);
        int count_equal_symbols = 0;
        for (int i = 0; i < first_string_modify_length; i++) {
            while (count_equal_symbols > 0 && second_string[count_equal_symbols] != first_string_modify[i]) {
                count_equal_symbols = prefix_function_second_string[count_equal_symbols-1];
            }
            if (second_string[count_equal_symbols] == first_string_modify[i]) {
                count_equal_symbols = count_equal_symbols + 1;
            }
            if (count_equal_symbols == second_string_length) {
                index_cycle_shift = i - second_string_length + 1;
                return index_cycle_shift;
            }       
        }
    }
    return index_cycle_shift;
}

// Функция, выводящая отформатированный ответ на 1 задание
// Принимает на вход вектор, хранящий индексы начала вхождений шаблона в текст
void printFirstTaskAnswer(std::vector<int> finding_index_inclusion) {
    if (finding_index_inclusion.size() != 0) {
        for (int i = 0; i < finding_index_inclusion.size() - 1; i++) {
            std::cout << finding_index_inclusion[i]<<",";
        }
        std::cout << finding_index_inclusion.back();
    }
    else {
        std::cout << pattern_not_in_text;
    } 
}

// Функция, запускающая решение 1 задания
void startFirstTaskSolution() {
    std::string pattern, text;
    std::cin >> pattern;
    std::cin >> text;
    std::vector<int> finding_index_inclusion = findOccurrenceInTextKMP(text, pattern);
    printFirstTaskAnswer(finding_index_inclusion);
}

// Функция, выводящая отформатированный ответ на 2 задание
// Принимает на вход значение, хранящее индекс начала второй строки в первой
void printSecondTaskAnswer(int index_begin_second_in_first) {
    if (index_begin_second_in_first == index_not_find) {
        std::cout << index_not_find;
    }
    else {
        std::cout << index_begin_second_in_first;
    } 
}

// Функция, запускающая решение 2 задания
void startSecondTaskSolution() {
    std::string first_string, second_string;
    std::cin >> first_string;
    std::cin >> second_string;
    int index_begin_second_in_first = checkCycleShiftKMP(first_string, second_string);
    printSecondTaskAnswer(index_begin_second_in_first);
}

int main() {
    startFirstTaskSolution();
    startSecondTaskSolution();
    return 0;
}