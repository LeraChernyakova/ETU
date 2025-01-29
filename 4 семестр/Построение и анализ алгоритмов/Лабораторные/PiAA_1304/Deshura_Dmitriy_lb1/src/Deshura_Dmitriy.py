#   Рекурсивная функция подстановки квадратов. На вход получает Битовую маску (mask), благодаря которой
# отслеживается заполнение квадрата, Размер исходного квадрата (N), Размер, Координату Х и Координату У
# текущего квадрата (size, x, y), Текущий рекорд (record) и Счётчик (counter).
#   Функция сначала подставляет на выбранное место квадрат выбранного размера, затем вычисляет следующую 
# свободную позицию и вызывает следующие шаги рекурсии, пытаясь подставить на заданное место все влазящие 
# квадраты. Наилучшие результаты запоминаются и заносятся в рекорд. Если квадрат заполнен, а рекорд не превышен,
# возвращаются координаты и размер текущего квадрата + текущий рекорд, в противном случае возвращается
# None + рекорд. После вставки каждого квадрата и нахождения координат следующего (и при этом квадрат не
# заполнен) происходит проверка: если текущий счётчик + 1 больше либо равен рекорду, то мы не получим
# лучшего решения, поэтому прерываемся и возвращаем None + рекорд.
#   На каждом шаге рекурсии мы вызываем следующий шаг для подстановки квадратов разных размеров. Размер квадрата 
# и дальнейшее заполнение, приводящие к текущему рекорду, запоминаются в переменные best_size и best_practice 
# соответственно, для последующего восстановления найденного решения.
def setShape (mask, N, size, x, y, record, counter):
    square = ((1 << size) - 1) << x
    counter += 1
    for i in range(y, y + size):
        mask[i] += square

    newX = 0
    newY = y
    fullString = (1 << N) - 1
    while newY < N and mask[newY] == fullString:
        newY += 1

    if newY == N:
        if record > counter:
            record = counter
            return [str(x + 1) + " " + str(y + 1) + " " + str(size)], record
        else:
            return None, record

    if counter + 1 >= record:
        return None, record

    currentString = mask[newY]
    while currentString % 2:
        newX += 1
        currentString = currentString >> 1
    
    best_size = None
    for i in range(N // 2, 0, -1):
        if (((1 << i) - 1) << newX) & ((1 << N) + mask[newY]) == 0 and (N - newY >= i): #если квадрат влазит и по ширине и по длине
            res, record = setShape (mask.copy(), N, i, newX, newY, record, counter)
            if res != None:
                best_size = size
                best_practice = res

    if best_size and best_practice:
        return [str(x + 1) + " " + str(y + 1) + " " + str(best_size)] + best_practice, record
    else:
        return None, record


# Функция, получающая на вход размер квадрируемого квадрата и возвращающая его разбиение. Формирует
# необходимые для рекурсивной функции переменные - маску (с вставленными начальными (см далее) квадратами),
# счётчик квадратов и начальный рекорд (уставливается равным 2*N+1, так как мы точно можем сказать, что
# существует разбиение из 2*N квадратов (большой со стороной N-1 и 2*N-1 маленьких)). Берём за основу тот факт,
# что в минимальном разбиении первые 3 квадрата - фиксированные (один N//2+1 и два квадрата по N-(N//2+1).
# Расположенные по 3м смежным углам)
def findShapes(N):
    result = []
    len_result = 2 * N + 1
    for side in range(N // 2 + 1, N // 2 + 2):
        answer = ["1 1 " + str(side), "1 " + str(side + 1) + " " + str(N - side)]
        mask = [(1 << side) - 1] * (side) + [(1 << (N - side)) - 1] * (N - side)
        answer_2 = setShape(mask, N, size=N-side, x=side, y=0, record=len_result, counter=2)[0]
        if answer_2 and len(answer_2) + 2 < len_result:
            result = answer + answer_2
            len_result = len(result)
    return result


# Основная функция программы. Считывает сторону квадрата, находит её наименьший делитель и коэффицент 
# на который необходимо увеличить решение. Запускает функцию findShapes с парметром N - находящую 
# минимальное квадрирование квадрата со стороной N и возвращает набор квадратов разбиения и их координат.
# В конце выводит ответ в необходимом формате, масштабирую, если необходимо, координаты и размеры квадратов. 
if __name__ == "__main__":
    N = int(input())
    smallest = N
    k = 1
    for i in range(2, N):
        if N % i == 0:
            smallest = i
            k = N // smallest
            break

    if smallest % 2:
        result = findShapes(smallest)
    else:
        result = ["1 1 1", "2 1 1", "1 2 1", "2 2 1"]
    print(len(result))
    for iter in result:
        x, y, w = map(int, iter.split())
        print(str((x - 1) * k + 1) + " " + str((y - 1) * k + 1) + " " + str(w * k))
