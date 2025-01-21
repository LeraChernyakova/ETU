from functools import cache
from typing import List
import numpy as np


def buildNurbs(T: List[float], P: List[np.array], W: List[float]):
    # Узлы - 1
    m = 9
    # Управляющие точки - 1
    n = 4
    # Степень сплайна
    k = 4

    # Базисные функции N(i, j)
    N = dict()

    # Генерация базисных функций порядка 0
    def buildNk1(t_i, t_i1):
        return lambda t: 1 if (t_i <= t <= t_i1) else 0

    for i in range(m):
        N[(i, 0)] = buildNk1(T[i], T[i + 1])

    # Генерация базисных функций k-го порядка
    def buildNkm(i, j):
        nonlocal N, T

        @cache
        def Nin(t):
            f = (t - T[i]) / (T[i + j] - T[i]) if (T[i + j] - T[i]) != 0 else 0
            g = (T[i + 1 + j] - t) / (T[i + 1 + j] - T[i + 1]) if (T[i + 1 + j] - T[i + 1]) != 0 else 0
            return f * N[(i, j - 1)](t) + (g) * N[(i + 1, j - 1)](t)

        return Nin

    for j in range(1, k + 1):
        for i in range(n - j + k + 1):
            N[(i, j)] = buildNkm(i, j)

    def F(t):
        f = [N[(i, k)](t) * W[i] for i in range(n + 1)]
        b1 = sum([f[i] * P[i] for i in range(n + 1)])
        b2 = sum([f[i] for i in range(n + 1)])
        return b1 / b2 if b2 != 0 else b1

    return F, N