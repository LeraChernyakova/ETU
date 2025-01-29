a = list(map(int, input().split())) # считывание списка

cnt = [0] * (max(a) + 1)  # генерация списка нулей длиной в максимальный элемент списка a

for item in a:
    cnt[item] += 1   # когда мы встречаем число в списке, увеличиваем его значение на 1

# добавляем count раз число num в результат
result = [num for num, count in enumerate(cnt) for i in range(count)]

print(result)  # выводим отсортированный список

'''
Мы создаём вспомогательный массив и на старте заполняем его нулями.
Проходим по всему исходному массиву и смотрим очередное значение в ячейке.
Берём содержимое этой ячейки и увеличиваем на единицу значение вспомогательного массива под этим номером. Например, если мы встретили число 5, то увеличиваем на единицу пятый элемент вспомогательного массива. Если встретили 13 — тринадцатый.
После цикла во вспомогательном массиве у нас хранятся данные, сколько раз встречается каждый элемент.
Теперь мы проходим по вспомогательному массиву, и если в очередной ячейке лежит что-то больше нуля, то мы в исходный массив столько же раз отправляем номер этой ячейки. Например, в первой ячейке вспомогательного массива лежит число 7. Это значит, что в исходный массив мы отправляем единицу 7 раз подряд.
'''


def counting_sort(alist, largest):
    c = [0] * (largest + 1)
    for i in range(len(alist)):
        c[alist[i]] = c[alist[i]] + 1

    # Find the last index for each element
    c[0] = c[0] - 1  # to decrement each element for zero-based indexing
    for i in range(1, largest + 1):
        c[i] = c[i] + c[i - 1]

    result = [None] * len(alist)

    # Though it is not required here,
    # it becomes necessary to reverse the list
    # when this function needs to be a stable sort
    for x in reversed(alist):
        result[c[x]] = x
        c[x] = c[x] - 1

    return result


alist = input('Enter the list of (nonnegative) numbers: ').split()
alist = [int(x) for x in alist]
k = max(alist)
sorted_list = counting_sort(alist, k)
print('Sorted list: ', end='')
print(sorted_list)