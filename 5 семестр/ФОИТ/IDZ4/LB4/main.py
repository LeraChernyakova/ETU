import math
import random

import matplotlib.pyplot as plt
import numpy as np

grid_rows = 100
grid_columns = grid_rows

e = 10 ** (-3)
v = 9
potential = 2

gradient_file_name = 'gradient'
contour_file_name = 'equipotentials'
result_file_name = 'result.txt'


def inner_electrode(x, y):
    return abs(-0.4 + x) ** 2 + abs(-0.5 + y) ** 2


def is_on_border(i, j, n):
    return i == 0 or j == 0 or i == n - 1 or j == n - 1


def distance_between_two_points(x0, y0, x1, y1):
    return math.sqrt(math.pow((x0 - x1), 2) + math.pow((y0 - y1), 2))


def index_to_coordinate(i, n):
    return (4 * i / n) - 2


def is_inside_electrode(x, y):
    return abs(inner_electrode(x, y)) < 0.95


def is_on_electrode(x, y):
    return abs(inner_electrode(x, y) - 1) < 0.05


def grid_with_electrode(grid):
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            x = index_to_coordinate(j, len(grid[i]))
            y = -index_to_coordinate(i, len(grid))

            if is_on_electrode(x, y) or is_inside_electrode(x, y):
                grid[i][j] = 9

    return grid


def get_grid(rows, columns):
    grid = np.empty([rows, columns])

    for i in range(rows):
        for j in range(columns):
            if is_on_border(i, j, rows):
                grid[i, j] = 0
            else:
                grid[i, j] = random.random() * v

    return grid


def calculations(grid, acc):
    accuracy = acc
    eps = 0.2

    grid_prev = grid.copy()

    while eps > accuracy:
        eps = 0
        for i in range(1, len(grid) - 1):
            for j in range(1, len(grid[i]) - 1):
                x = index_to_coordinate(j, len(grid[i]))
                y = -index_to_coordinate(i, len(grid))

                if is_inside_electrode(x, y) or is_on_electrode(x, y):
                    continue

                grid[i][j] = (grid_prev[i - 1][j] + grid[i + 1][j] + grid[i][j + 1] + grid_prev[i][j - 1]) / 4
                eps = max(eps, abs(grid_prev[i][j] - grid[i][j]))
        grid_prev = grid.copy()

    return grid_prev


def show_gradient(grid):
    plt.imshow(grid, cmap='jet', interpolation='nearest')
    plt.savefig(gradient_file_name)
    plt.show()


def show_contour(grid, ax):
    contour_plot = ax.contour(grid, [i for i in range(1, v)], cmap='jet')
    ax.clabel(contour_plot, inline=True, fontsize=12)
    plt.savefig(contour_file_name)
    plt.show()
    return contour_plot


grid = get_grid(grid_rows, grid_columns)
grid = grid_with_electrode(grid)
grid = calculations(grid, e)

show_gradient(grid)

fig, ax = plt.subplots()
contour_plot = show_contour(grid, ax)

contour_coords = contour_plot.allsegs[potential - 1][0]
result = 0
for i in range(1, len(contour_coords)):
    x0 = index_to_coordinate(contour_coords[i - 1][0], grid_rows)
    y0 = -index_to_coordinate(contour_coords[i - 1][1], grid_columns)
    x1 = index_to_coordinate(contour_coords[i][0], grid_rows)
    y1 = -index_to_coordinate(contour_coords[i][1], grid_columns)
    tmp = distance_between_two_points(x0, y0, x1, y1)
    result += tmp

file = open(result_file_name, 'w')
file.write(str(result))
file.close()
