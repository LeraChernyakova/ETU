prime = 101
x = 128


def hashing(string):
    hashing_value = 0
    for k in range(len(string)):
        hashing_value = (x * hashing_value + ord(string[k])) % prime
    return hashing_value


def algorithm_rabin_karp(pattern, text):
    result = list()
    pl = len(pattern)
    tl = len(text)
    h = 1

    if pl > tl:
        print('Длина подстроки превышает текст')
        return -1

    if pl == 0 or tl == 0:
        print('Введены пустые строки')
        return -1

    pattern_hash = hashing(pattern)
    win_hash = hashing(text[:pl])

    for _ in range(pl - 1):
        h = (h * x) % prime

    for j in range(0, tl - pl + 1):

        if pattern_hash == win_hash:
            if pattern == text[j: j + pl]:
                result.append(j)

        if j + pl < tl:
            win_hash = (x*(win_hash-ord(text[j])*h) + ord(text[j + pl])) % prime

            if win_hash < 0:
                win_hash += prime

    return result


if __name__ == '__main__':
    Pattern = input()
    Text = input()
    answer = algorithm_rabin_karp(Pattern, Text)
    if answer != -1:
        if len(answer) != 0:
            for i in range(len(answer)):
                print(answer[i], end=' ')
        else:
            print('Вхождения не найдены!')
