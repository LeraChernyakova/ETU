# coding=utf-8
import math
import matplotlib.pyplot as plt

L = 42  # length of canal
D = 1.2  # diameter
n2 = 1
a = 32
N = 1000  # parts
step = D / N  # size of one part
array_x = [0]
array_y = [0]
S = 0


def get_new_alpha(alpha, nextY, n1):  # закон Снеллиуса (ищем новый угол)
    sinB = math.sin(alpha) * n1 / nextY
    if math.fabs(sinB) > 1:
        return -alpha, n1  # полное отражение
    return math.asin(sinB), nextY  # преломление


def get_n1(cur_y):
    if D > cur_y > -D:
        return 1.5 + 0.3 * (math.cos(0.8 * cur_y)) ** 3
    return n2


x, y = 0, 0
n1 = get_n1(y)  # start n1
alpha = math.pi / 2 - math.radians(a)  # 90 - стартовый угол
while x < L:
    nextX = x + math.fabs(math.tan(alpha) * step)
    nextY = y + (nextX - x) / math.tan(alpha)
    S += math.sqrt((nextX - x) ** 2 + (nextY - y) ** 2)  # теорема Пифагора
    x, y = nextX, nextY
    array_x.append(x)
    array_y.append(y)
    alpha, n1 = get_new_alpha(alpha, get_n1(nextY), n1)

print(S)
fig, ax = plt.subplots()
ax.set_xlabel('Z')
ax.set_ylabel('Y')
plt.grid()
plt.savefig("lab1.png")
ans = open('result.txt', 'w')
ans.write(str(S))
ans.close()
plt.plot(array_x, array_y, color='b')
plt.hlines(D, 0, 50, linewidth=3)
plt.hlines(-D, 0, 50, linewidth=3)
plt.show()
