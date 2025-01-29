def compute_LPS_array(pattern, pattern_length):
    """
    Вычисляет массив LPS для заданного шаблона.

    Аргументы:
    pattern -- шаблон, для которого вычисляется массив LPS
    pattern_length -- длина шаблона

    Возвращает:
    массив LPS для заданного шаблона
    """
    longest_proper_prefix = 0
    lps_array = [0] * pattern_length
    i = 1
    while i < pattern_length:
        if pattern[i] == pattern[longest_proper_prefix]:
            longest_proper_prefix += 1
            lps_array[i] = longest_proper_prefix
            i += 1
        else:
            if longest_proper_prefix != 0:
                longest_proper_prefix = lps_array[longest_proper_prefix - 1]
            else:
                lps_array[i] = 0
                i += 1
    return lps_array

def KMP(string, pattern):
    """
    Реализация алгоритма Кнута-Морриса-Пратта для поиска всех вхождений образца в строку.

    Аргументы:
    string -- строка, в которой ищутся вхождения образца
    pattern -- образец, вхождения которого ищутся в строке

    Возвращает:
    строку, содержащую индексы всех вхождений образца в строке через запятую, если они найдены, или -1, если образец     не найден.
    """
    pattern_length = len(pattern)
    string_length = len(string)
    lps_array = compute_LPS_array(pattern, pattern_length)
    i, j = 0, 0
    matches = []

    while i < string_length:
        if string[i] == pattern[j]:
            i += 1
            j += 1
            if j == pattern_length:
                matches.append(str(i-j))
                j = lps_array[j-1]
        else:
            if j != 0:
                j = lps_array[j-1]
            else:
                i += 1

    if len(matches) == 0:
        return '-1'
    return ','.join(matches)

if __name__ == '__main__':
    pattern = input()
    string = input()
    print(KMP(string, pattern))