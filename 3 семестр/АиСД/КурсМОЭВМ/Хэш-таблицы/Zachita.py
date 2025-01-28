prime = 101
x = 128


def hashing(string):
    hashing_value = 0
    for k in range(len(string)):
        hashing_value = (x * hashing_value + ord(string[k])) % prime
    return hashing_value


print('Введите количество строк, которое хотите сравнить')
n = int(input())
strings = list()
print('Вводите строки:')
for i in range(n):
    strings.append(input())
strings_hash = dict()
for i in range(len(strings)):
    if hashing(strings[i]) in strings_hash:
        strings_hash[hashing(strings[i])] += 1
    else:
        strings_hash[hashing(strings[i])] = 1

cnt_answer = 0
for keys in strings_hash:
    if (strings_hash[keys] == 1):
        cnt_answer += 1
print('Различных слов - ', cnt_answer)
