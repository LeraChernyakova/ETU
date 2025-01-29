def is_empty_area(added, x, y, k):  # проверка на возможность вставки квадрата
    for i in added:
        if x < i[0] + i[2] and x + k > i[0] and y < i[1] + i[2] and y + k > i[1]:
            return False
    return True


def get_optimal_start():  # установка первых трех квадратов для оптимального старта
    backtracking(
        {
            (0, 0, (n + 1) // 2),
            (0, (n + 1) // 2, (n - 1) // 2),
            ((n + 1) // 2, 0, (n - 1) // 2),
        },
        ((n + 1) // 2) ** 2 + 2 * (n - (n + 1) // 2) ** 2,
    )


def backtracking(
        added, ocup_area
):  # функция, которая перебирает все варианты и возвращает наилучший
    global ans
    if ocup_area < n ** 2 and len(added) + 1 >= ans:
        return
    if len(added) < ans and ocup_area == n * n:
        global ans_mass
        ans, ans_mass = len(added), added
        return

    for size_of_input in submatriсes.keys():
        if size_of_input ** 2 <= (n * n - ocup_area):
            for elem in submatriсes[size_of_input]:
                if is_empty_area(added, elem[0], elem[1], size_of_input):
                    if not ((elem[0], elem[1], size_of_input) in added):
                        backtracking(
                            added.union({(elem[0], elem[1], size_of_input)}),
                            size_of_input * size_of_input + ocup_area,
                        )
                        if size_of_input == 1 or size_of_input == 2:
                            return
                        break


def sol_for_even():  # вывод решения для четных
    print(4)
    print(0, 0, n // 2)
    print(0, n // 2, n // 2)
    print(n // 2, 0, n // 2)
    print(n // 2, n // 2, n // 2)
    exit(0)


def sol_for_multiple3():  # вывод решения для кратных 3
    get_optimal_start()
    print(ans)
    for i in ans_mass:
        print(i[0] * koeff, i[1] * koeff, i[2] * koeff)


def sol_for_else():  # вывод решения для остальных
    get_optimal_start()
    print(ans)
    for i in ans_mass:
        print(*i)


n = int(input())
if n % 3 == 0 and n % 2 != 0:
    koeff, n = n // 3, 3
ans, ans_mass, submatriсes = 14, {}, {}
for k in reversed(range(n - (n + 1) // 2)):
    submatriсes[k + 1] = [
        (i, j)
        for i in reversed(range(n // 2, n - k))
        for j in reversed(range(n // 2, n - k))
    ]
if n % 2 == 0:
    sol_for_even()
elif n % 3 == 0:
    sol_for_multiple3()
else:
    sol_for_else()
