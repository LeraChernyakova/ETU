from copy import deepcopy


class MapSquare:  # основной класс столешницы, на котором базируется вся 
задача
    def __init__(self, n):
        self.n = n  # сторона столешницы
        self.free_s = self.n ** 2  # свободная площадь столешницы, 
изначально свободна вся
        self.map_square = [[0] * n for _ in range(n)]  # двумерный массив 
для хранения заполненности столешницы (0 - свободно)
        self.best_map = []  # список для хранения координат левого угла и 
длины стороны вствленных квадратов
        self.best_square_counter = 400  # наименьшее количество квадратов 
для заполнения(так как рассматривается задача до 20, то наихудший вариант 
20*20=400)

    def best_start(self):  # оптимизация: лучшая начальная вставка трех 
квадратов в правый нижний угол и смежных с ним
        for h in range(self.n // 2, self.n):  # вставка большого квадрата 
со стороной (n + 1) // 2
            for w in range(self.n // 2, self.n):
                self.map_square[h][w] = 1
        self.best_map.append([self.n // 2, self.n // 2, (self.n + 1) // 
2])

        for h in range(self.n // 2):  # вставка смежного квадрата со 
стороной (n + 1) // 2 - 1
            for w in range(self.n // 2 + 1, self.n):
                self.map_square[h][w] = 2
        self.best_map.append([0, self.n // 2 + 1, (self.n + 1) // 2 - 1])

        for h in range(self.n // 2 + 1, self.n):  # вставка еще одного 
смежного квадрата со стороной (n + 1) // 2 - 1
            for w in range(self.n//2):
                self.map_square[h][w] = 3
        self.best_map.append([self.n // 2 + 1, 0, (self.n + 1) // 2 - 1])

    @staticmethod
    def can_insert(map_sq, insert_n, x, y):  # проверка на вставку 
квадрата со стороной insert_n на позицию x y
        for h in range(y, y + insert_n):
            for w in range(x, x + insert_n):
                if map_sq[h][w] != 0:
                    return False
        return True

    @staticmethod
    def insert_square(map_sq, insert_n, numb, x, y):  # вставка квадрата 
со стороной insert_n и номером numb на позицию x y и возврат новой карты 
столешницы
        new_map = deepcopy(map_sq)
        for h in range(y, y + insert_n):
            for w in range(x, x + insert_n):
                new_map[h][w] = numb
        return new_map

    def solve(self):  # основной метод, вызываемый из main
        if self.n % 2 == 0:  # оптимизация: если размер стороны столешницы 
четный, то поле разбивается на 4 квадрата со сторонами n/2
            self.best_square_counter = 4
            self.best_map.append([0, 0, self.n // 2])
            self.best_map.append([self.n // 2, 0, self.n // 2])
            self.best_map.append([0, self.n // 2, self.n // 2])
            self.best_map.append([self.n // 2, self.n // 2, self.n // 2])
            return

        if self.n % 3 == 0:   # оптимизация: является ли кратным 3
            k = self.n // 3  # коэффициент пропорциональности
            self.best_square_counter = 6  # на практике доказано, что 
квадрат 3x3 и квадраты со стороной кратной 3 можно минимально разбить на 6 
квадратов
            # ниже представлены параметры квадратов на вставку, умноженные 
на коэффициент пропорцилональности
            self.best_map.append([k, k, k * 2])
            self.best_map.append([k * 2, 0, k])
            self.best_map.append([0, k * 2, k])
            self.best_map.append([0, 0, k])
            self.best_map.append([0, k, k])
            self.best_map.append([k, 0, k])
            return

        # для оставшихся чисел используется перебор
        self.best_start()
        counter = 3  # счетчик вставленных квадратов (3, так как 3 
квадрата уже вставлены функцией best_start)
        map_square = deepcopy(self.map_square)
        free_s = n ** 2 - ((self.n + 1) // 2) ** 2 - 2 * (((self.n + 1) // 
2 - 1) ** 2)  # свободная площадь уменьшается на площадь вставленных 
квадратов
        best_map = deepcopy(self.best_map)
        self.find_square(map_square, free_s, counter, best_map)  # 
рекурсивная функция поиска наилучшего расположения квадратов

    def find_square(self, map_square, free_s, counter, best_map):  # поиск 
вставки квадрата (рекурсивная реализация)
        if counter >= self.best_square_counter:  # выход из рекурсии если 
счетчик достигает или превышает лучшее количество квадратов
            return
        for h in range(self.n // 2 + 1):  # перебор строк
            for w in range(self.n // 2 + 1):  # перебор столбцов
                for insert_n in range(self.n // 2, 0, -1):  # перебор 
размеров квадратов на вставку
                    if map_square[h][w] == 0 and 
self.can_insert(map_square, insert_n, w, h):  # проверка на вставку
                        new_map_square = self.insert_square(map_square, 
insert_n, counter + 1, w, h)
                        new_result = deepcopy(best_map)
                        new_result.append([h, w, insert_n])
                        if free_s - insert_n * insert_n > 0:  # проверка 
заполнен ли квадрат
                            self.find_square(new_map_square, free_s - 
insert_n * insert_n, counter + 1, new_result)
                            if h != 0 and w != 0:  # перебор вставок не в 
верхний левый угол - повторение уже проверенных расстановок
                                return
                        else:
                            if counter < self.best_square_counter:  # 
проверка для обновления текущего наилучшего расположения
                                self.map_square = deepcopy(new_map_square)
                                self.best_square_counter = counter + 1
                                self.best_map = deepcopy(new_result)
                            return
                        if insert_n == 1:
                            return

    def __str__(self):  # реализует требуемый вывод: количество квадратов 
и параметры каждого из них
        res = str(self.best_square_counter) + '\n'
        for i in range(self.best_square_counter):
            # +1 к координатам так как в массиве идет нумерация с нуля, а 
в задаче с единицы
            res = res + str(self.best_map[i][0] + 1) + ' ' + 
str(self.best_map[i][1] + 1) + ' ' + str(self.best_map[i][2]) + '\n'
        return res


if __name__ == "__main__":
    n = int(input())
    map_square = MapSquare(n)
    map_square.solve()
    print(map_square)
