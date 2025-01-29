import math
import matplotlib.pyplot as plt
import numpy as np

alpha_0 = math.radians(90 - 25)
delta_y = 0.0001
max_y = 0.7
L = 25


def func_refractive(y):
    return 1.2 - 0.3 * y ** 2


def calculate_sin_beta(sin_alpha, n_1, n_2):
    return sin_alpha * n_1 / n_2

def calculate_s(sin_alpha, y):
    return y/(math.sqrt(1 - sin_alpha**2))


def calculate_z(sin_alpha, y):
    return y / math.sqrt(1 / sin_alpha ** 2 - 1)


sin_alpha = math.sin(alpha_0)
n_1 = func_refractive(0)
points_z = []
points_y = []
z = 0
y = 0
s = 0
while z < L:
    n_2 = func_refractive(y)
    sin_beta = calculate_sin_beta(sin_alpha, n_1, n_2)
    if sin_beta >= 1:
        sin_beta = sin_alpha
        delta_y = - delta_y
        y += delta_y
        continue
    s += calculate_s(sin_beta, np.abs(delta_y))
    z += calculate_z(sin_beta, np.abs(delta_y))
    n_1 = n_2
    sin_alpha = sin_beta
    points_z.append(z)
    points_y.append(y)
    if np.abs(y) > max_y:
        delta_y = - delta_y
    y += delta_y


plt.axis([0, L, -max_y, max_y])
plt.grid(True)
plt.plot(points_z, points_y)
plt.show()
print(s)