import matplotlib.pyplot as plt
from main import RBTree
import time
import math

tree = RBTree()

x = list()
y = list()

for i in range(1, 5000):
    x.append(i)
    elem = math.log(i, 2) * 5000
    y.append(elem)

# генерация входного массива
elements = list()
for i in range(5000):
    elements.append(i)

time_search = list()

for i in range(5000):
    #вставка
    tree.insert(elements[i])

    # поиск
    start_time = time.perf_counter_ns()
    tree.search(elements[i])
    end_time = time.perf_counter_ns()
    time_search.append(end_time - start_time)

# построение графика
plt.title("Исследование сложности операции поиска в КЧ дереве")   # Название таблицы
plt.xlabel("Количесво элементов")                           # ось абсцисс
plt.ylabel("Время, нс")                                     # ось ординат
plt.grid()                                                  # включение отображение сетки

# теоритический график каждой операции
plt.scatter(elements, time_search, s=5)  # построение графика
plt.scatter(x, y, s=5)
plt.legend(["Практическая сложность ", "Теоритическая сложность"])

plt.show()
