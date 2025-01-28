class Square:
  """Класс квадратного обрезка столешницы."""

  def __init__(self, x, y, w):
    """Конструктор, принимает координаты левого верхнего угла столешницы по
    осям оХ и оУ, длину стороны обрезка типа int"""
    self.x = x
    self.y = y
    self.w = w

n = int(input())
bestcount = 2 * n + 1
bestarray = []
boardsize = 0

for i in range(1, n):
  if (n % i == 0):
    boardsize = i

n //= boardsize

table = []
table.append(Square(0, 0, (n + 1) // 2))
table.append(Square(0, (n + 1) // 2, n // 2))
table.append(Square((n + 1) // 2, 0, n // 2))


def Collision(one, x, y):
  """Функция, проверяющая, занята ли точка столешницы one по целочисленным
  координатам х и у, возвращая True или False"""
  for square in one:
    if (x >= square.x and x < square.x + square.w and y >= square.y
        and y < square.y + square.w):
      return True
  return False


def Backtracking(one, summ, boardlen, minx, miny):
  """Функция, ищущая наилучшее разложение столешницы one с занятой площадью 
  summ, количеством обрезков boardlen начиная c координат minx и miny. 
  Записывает ответ в переменную bestarraray"""
  global bestcount
  for x in range(minx, n):
    for y in range(miny, n):
      if (not Collision(one, x, y)):
        right = min(n - x, n - y)
        for square in one:
          if (square.x + square.w > x and square.y > y):
            right = min(right, square.y - y)

        for r in range(right, 0, -1):
          square = Square(x, y, r)
          b = one.copy()
          b.append(square)
          if (summ + square.w * square.w == n * n):
            # обновление ответа
            if (boardlen + 1 < bestcount):
              bestcount = boardlen + 1
              bestarray[:] = b.copy()

          else:
            if (boardlen + 1 < bestcount):
              Backtracking(b, summ + square.w * square.w, boardlen + 1, x,
                           y + r)
            else:
              return
        return
    miny = n // 2


Backtracking(
  table,
  (n + 1) // 2 * (n + 1) // 2 + 2 * n // 2 * n // 2, 3,
  n // 2, (n + 1) // 2)

print(len(bestarray))

for i in bestarray:
  print(
    str(i.x * boardsize) + ' ' + str(i.y * boardsize) + ' ' +
    str(i.w * boardsize))
