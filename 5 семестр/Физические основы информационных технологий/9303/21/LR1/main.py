import math

import matplotlib.pyplot as plt

# Program parameters
D = 1.2  # diameter
L = 42   # length
a = 32   # alpha angle

n = 1000      # number of layers
h = D / n     # layer size
n2 = 1


# sin(a) * n1 = sin(b) * n2
# sin(b) = (sin(a) * n1) / n2


def n_calculate(y):
    if D > y > -D:
        return 1.5 + 0.3 * ((math.cos(0.8 * y)) ** 2)
    else:
        return n2


def next_alpha(alpha, next_y, n1_last):
    beta = (math.sin(alpha) * n1_last) / n_calculate(next_y)

    if math.fabs(beta) <= 1:
        return math.asin(beta), n_calculate(next_y)
    else:
        return -alpha, n1_last


def next_coords(x, y, alpha):
    k = math.tan(alpha)

    next_x = x + math.fabs(k * h)
    next_y = y + ((next_x - x) / k)
    return next_x, next_y


def calculate_distance_between_points(x, y, x1, y1):
    return math.sqrt((x1 - x) ** 2 + (y1 - y) ** 2)


def calculate_trajectory(length, angle):
    result = 0.0
    x, y = 0.0, 0.0
    points = [(x, y)]
    n1_last = n_calculate(y)

    alpha = math.pi / 2 - math.radians(angle)

    while x < length:
        next_x, next_y = next_coords(x, y, alpha)
        alpha, n1_last = next_alpha(alpha, next_y, n1_last)

        result += calculate_distance_between_points(x, y, next_x, next_y)

        x, y = next_x, next_y
        points.append((x, y))

    return result, points


def plot_s(points, height):
    plt.plot([p[0] for p in points], [p[1] for p in points], color='r')
    plt.savefig("graphics.png")
    plt.axhline(height / 2, xmin=0, xmax=L)
    plt.axhline(-height / 2, xmin=0, xmax=L)
    plt.show()


s, p = calculate_trajectory(L, a)

with open("result.txt", "w") as f:
    print(s, file=f)

plot_s(p, D)

