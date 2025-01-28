def get_longest_prefix_suffix(pattern, pattern_length):
    """
    Эта функция вычисляет массив самого длинного корректного префикса, который также является суффиксом (LPS),
    для заданного образца.
    
    Аргументы:
    pattern (str): Входной образец, для которого требуется вычислить массив LPS.
    pattern_length (int): Длина входного образца.
    
    Возвращает:
    list: Список, содержащий значения LPS для заданного образца.
    """
    lps_array = [0] * pattern_length
    for idx in range(1, pattern_length):
        prev_lps = lps_array[idx - 1]
        while prev_lps > 0 and not pattern[prev_lps] == pattern[idx]:
            prev_lps = lps_array[prev_lps - 1]
        if pattern[prev_lps] == pattern[idx]:
            prev_lps = prev_lps + 1
        lps_array[idx] = prev_lps
    return lps_array

def circular_shift(string, pattern):
    """
    Эта функция проверяет, можно ли получить заданный образец путем циклического сдвига (вращения) входной строки.
    Если образец можно получить, функция возвращает индекс первого символа во входной строке после сдвига;
    в противном случае возвращает '-1'.
    
    Аргументы:
    string (str): Входная строка для проверки.
    pattern (str): Образец, который может быть или не быть получен путем циклического сдвига входной строки.
    
    Возвращает:
    str: Индекс первого символа после сдвига в виде строки или '-1', если образец нельзя получить путем сдвига.
    """
    if len(string) != len(pattern):
        return '-1'
    lps = get_longest_prefix_suffix(pattern, len(pattern))
    string_length = len(string)
    pattern_length = len(pattern)
    string_idx = 0
    pattern_idx = 0
    while pattern_idx < pattern_length:
        if string[string_idx % string_length] == pattern[pattern_idx]:
            if pattern_idx == pattern_length - 1:
                return str((string_idx + 1) % string_length)
            else:
                pattern_idx += 1
        else:
            if pattern_idx == pattern_length - 1:
                return '-1'
            if pattern_idx != 0:
                pattern_idx = lps[pattern_idx - 1]
                continue
        string_idx += 1
    return '-1'

if __name__ == '__main__':
    input_string = input()
    input_pattern = input()
    print(circular_shift(input_string, input_pattern))