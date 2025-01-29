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

for i in range(5000):
    tree.insert(elements[i])

time_delete = list()

for i in range(5000):
    #удаление
    start_time = time.perf_counter_ns()
    tree.delete(elements[i])
    end_time = time.perf_counter_ns()
    time_delete.append(end_time - start_time)

time_delete.reverse()

# построение графика
plt.title("Исследование сложности операции удаления в КЧ дереве")   # Название таблицы
plt.xlabel("Количество элементов")                           # ось абсцисс
plt.ylabel("Время, нс")                                     # ось ординат
plt.grid()                                                  # включение отображение сетки

# теоритический график каждой операции
plt.scatter(elements, time_delete, s=5)  # построение графика
plt.scatter(x, y, s=5)
plt.legend(["Практическая сложность", "Теоритическая сложность"])

plt.show()
