#include <iostream>
#include <vector>

// Нахождение префикс-функции
std::vector<int> generate_prefix_function(std::string needle) {
    std::vector<int> prefixFunction(needle.length());
    for (int right_index = 1; right_index < needle.length(); right_index++) {
        int left_index = prefixFunction[right_index - 1];
        while (left_index > 0 && needle[left_index] != needle[right_index]) {
            left_index = prefixFunction[left_index - 1];
        }
        if (left_index > 0 || needle[left_index] == needle[right_index]) {
            left_index++;
        }
        prefixFunction[right_index] = left_index;
    }
    return prefixFunction;
}

// Алгоритм Кнута–Морриса-Пратта
void kmp(std::string haystack, std::string needle) {
    std::string result;
    std::vector<int> prefixFunction = generate_prefix_function(needle);
    for (int haystack_iterator = 0, needle_iterator = 0; haystack_iterator < haystack.length(); haystack_iterator++) {
        if (needle_iterator < needle.length() && haystack[haystack_iterator] == needle[needle_iterator]) {
            if (++needle_iterator == needle.length()) {
                if (result.length() > 0) {
                    result.append(",");
                }
                result.append(std::to_string(haystack_iterator - needle_iterator + 1));
            }
        } else if (needle_iterator > 0) {
            needle_iterator = prefixFunction[needle_iterator - 1];
            haystack_iterator--;
        }
    }
    std::cout << (result.length() > 0 ? result : "-1");
}

 /*
  * Модификация алгоритма Кнута–Морриса-Пратта
  * Возвращает количество букв, на которое вторая строка сдвинута относительно первой
  * Если вторая строка не является сдвигом первой, возвращается -1
  */
void kmp_circle(std::string haystack, std::string needle) {
    if (haystack.length() != needle.length()) {
        std::cout << -1;
        return;
    }
    haystack = haystack + haystack;
    std::vector<int> prefix_function = generate_prefix_function(needle);
    for (int haystack_iterator = 0, needle_iterator = 0; haystack_iterator < haystack.length() - needle.length() + needle_iterator; haystack_iterator++) {
        if (needle_iterator < needle.length() && haystack[haystack_iterator] == needle[needle_iterator]) {
            if (++needle_iterator == needle.length()) {
                std::cout << needle.length() - haystack_iterator % needle.length() - 1;
                return;
            }
        } else if (needle_iterator > 0) {
            needle_iterator = prefix_function[needle_iterator - 1];
            haystack_iterator--;
        }
    }
    std::cout << -1;
}

// Точка входа в программу
int main() {
    std::string needle, haystack;
    std::cin >> needle >> haystack;
    kmp(haystack, needle);
    //kmp_circle(haystack, needle);
    return 0;
}