import math
import matplotlib.pyplot as plt


L = 28
D = 0.8
n2 = 1
N = 1000


def n1(y):
    return 1.4 - 0.12 * math.cos(5*y)


def algorithm():
    y = 0
    z = 0

    y_arr = [y]
    z_arr = [z]

    alpha = 20
    n_old = n1(y)
    mode = True
    S = 0
    dy = D / N

    while z < L:
        n1_new = n1(y + dy) if abs(y + dy) < D else 1
        if math.sin(math.radians(90 - alpha)) > (n1_new / n_old) and mode:
            mode = False
            alpha = -alpha
        elif math.sin(math.radians(90 - alpha)) > (n1_new / n_old) and not mode:
            mode = True
        y, z, alpha, n_old, S = step_algorithm(y, z, alpha, n_old, mode, S)
        y_arr.append(y)
        z_arr.append(z)
    return y_arr, z_arr, S


def step_algorithm(y, z, alpha, n_old, to_top, S):
    dy = D / N
    if to_top:
        y_new = y + dy
    else:
        y_new = y - dy
    n1_new = n1(y_new)
    alpha_new = math.asin(math.sin(math.radians(90 - alpha)) * (n_old / n1_new))
    z_new = z + (dy / math.tan(math.radians(alpha)))
    S += dy / math.sin(math.radians(alpha))
    return y_new, z_new, 90 - math.degrees(alpha_new), n1_new, S


def plot(z, y):
    plt.plot(z, [D for i in range(len(z))])
    plt.plot(z, [-D for i in range(len(z))])
    plt.plot(z, y)
    plt.savefig('graph.png')


def write_trajectory(S):
    file = open('result.txt', 'w')
    file.write(str(S))
    file.close()


def main():
    y, z, S = algorithm()
    plot(z, y)
    write_trajectory(S)


if __name__ == "__main__":
    main()
