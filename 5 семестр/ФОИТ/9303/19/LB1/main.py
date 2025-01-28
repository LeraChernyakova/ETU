import math
import matplotlib.pyplot as plt

D = 1.8
L = 12
alpha_0 = math.radians(90 - 42)
dy = 0.0001
n2 = 1


def n(y):
    return 1.4 + 0.3 * math.cos(math.radians(0.8 * pow(y, 4)))


def calc_sin_beta(sin_alpha, n1, n2):
    return sin_alpha * n1 / n2


def calculate_trajectory(dy):
    z, y = 0.0, 0.0
    points = [(z, y)]
    sin_alpha = math.sin(alpha_0)
    n1 = n(y)
    res = 0.0
    while z < L:
        n2 = n(y)
        sin_beta = calc_sin_beta(sin_alpha, n1, n2)
        if abs(y + dy) > D or sin_beta >= 1:
            dy = -dy
            sin_beta = sin_alpha
        res += abs(dy) / (math.sqrt(1 - sin_beta ** 2))
        z += abs(dy) / math.sqrt(1 / sin_beta ** 2 - 1)
        n1 = n2
        sin_alpha = sin_beta
        points.append((z, y))
        y += dy

    return res, points


def show_plot(points, D):
    plt.axis([0, L+0.2, -D-0.2, D+0.2])
    plt.grid(True)
    plt.plot([point[0] for point in points], [point[1] for point in points], color='b')
    plt.show()


def res_to_file(res):
    with open("result.txt", 'w') as file:
        file.write(str(res))


if __name__ == "__main__":
    result, points = calculate_trajectory(dy)
    print("Result: ", result)
    res_to_file(result)
    show_plot(points, D)
