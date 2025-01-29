from copy import deepcopy

class State: #класс, характеризующий текущее состояние столешницы с занятой точкой.
    def __init__(self, n): #является конструктором класса 
    #self- Это ссылка на текущие объекты класса и используется для доступа к переменной n этого класса.
    #n- размер стороны большого квадрата
        self.field = [[False] * (n + 1) for i in range(n + 1)]
        self.field[1][1] = True
        self.squares = []
        self.n = n

    def place_square(self, square): #методы для размещения квадрата
        self.squares.append(square)
        y, x, width = square
        #x, y- координата х, координата y квадрата
        #width- ширина квадрата 
        for i in range(y, y + width):
            for j in range(x, x + width):
                self.field[i][j] = True     

    def can_be_placed(self, square): # метод, которая дает информацию о том, можно ли этот квадрат разместить
        y, x, width = square
        if x + width - 1 > self.n or y + width - 1 > self.n:
            return False

        for i in range(y, y + width):
            if self.field[i][x + width - 1]:
                return False

        for i in range(x, x + width):
            if self.field[y + width - 1][i]:
                return False

        return True 

    def get_free_point(self): #метод для нахождения первого свободного левого верхнего угла
        for i in range(1, self.n+1):
            for j in range(1, self.n+1):
                if not self.field[i][j]:
                    return [i, j]

        return None 


def convert(coord, wide): #преобразовывает координату в соответствии с делителем
    return (coord - 1) * wide + 1


def back_tracking(start, max_deep, n): #функция итеративного бэк-трекинга. Массив states хранит состояния в виде объектов класса State
    states = [start]
    while True:
        next_states = []
        for i, state in enumerate(states):
            if len(state.squares) == max_deep:
                return None
            first_point = state.get_free_point()

            if not first_point:
                return state
            for width in range(1, n // 2 + 2):
                square = [first_point[0], first_point[1], width]
                if state.field[first_point[0]][first_point[1]]:
                    break
                if state.can_be_placed(square):
                    new_state = deepcopy(state)
                    new_state.place_square(square)
                    next_states.append(new_state)
                else:
                    break
        states = deepcopy(next_states)


def create_state(first_width, second_width, n):
    '''
    помещает квадраты в верхний левый
    и правый нижний углы.
    '''
    state = State(n)
    state.place_square([n - first_width + 1, 1, first_width])
    state.place_square([1, n - second_width + 1, second_width])
    return state

def solve_square_punct(bias, n, num, wide): #функция, которая осуществляет нахождение оптимальной расстановкидля квадрата с занятой точкой
                                            #Осуществляет размещение двух первых квадратов и передает управление функции back_tracking, bias - это смещение
                                            #n- это размер квадрата с выколотой точко
                                            #num- номер квадрата выводить
                                            #wide- ширина новой координатной сетки
    max_deep = 2 * n + 1
    best_way = None
    end = n // 4

    for i in range(n // 2 + 1, end, -1):
        for j in range(i, end, -1):
            if j + i > n:
                continue

            start = create_state(i, j, n)
            result = back_tracking(start, max_deep, n)
            if result:
                if len(result.squares) < max_deep:
                    max_deep = len(result.squares)
                    best_way = result

    print(max_deep + num)
    for i in range(len(best_way.squares)):
        print("{0} {1} {2}".format(convert(bias - 1 + best_way.squares[i][1], wide), convert(bias - 1 + best_way.squares[i][0], wide), \
            best_way.squares[i][2] * wide))

def place_big_squares(n, wide): #функция, которая помещает первые три (четыре) квадрата и вызывает функцию solve_square_punct,  n- размер стороны большого квадрата
    divider = n - 1
    if n % 2 == 0:
        width = n // 2
        print(4)
        print("{0} {1} {2}".format(convert(1, wide), convert(1, wide), width * wide))
        print("{0} {1} {2}".format(convert(width + 1, wide), convert(1, wide), width * wide))
        print("{0} {1} {2}".format(convert(1, wide), convert(width + 1, wide), width * wide))
        print("{0} {1} {2}".format(convert(width + 1, wide), convert(width + 1, wide), width * wide))
    else:
        biggest_square = n // 2 + 1
        solve_square_punct(biggest_square, biggest_square, 3, wide)
        print("{0} {1} {2}".format(convert(1, wide), convert(1, wide), biggest_square * wide))
        print("{0} {1} {2}".format(convert(biggest_square + 1, wide), convert(1, wide), (biggest_square - 1) * wide))
        print("{0} {1} {2}".format(convert(1, wide), convert(biggest_square + 1, wide), (biggest_square - 1) * wide))


def solve(n): #функция, которая находит наименьший делитель стороны квадрата и вызывает функцию place_big_squares
    divider = n - 1
    wide = 1
    while divider != 1:
        if n % divider == 0:
            wide *= divider
            n //= divider
            divider = n - 1
        else:
            divider -= 1
    place_big_squares(n, wide)


if __name__ == "__main__":
    N = int(input())
    solve(N)

