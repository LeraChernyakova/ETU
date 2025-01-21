import numpy as np


def func(x1: float, x2: float, a: float) -> float:
    return (x2 - x1**2) ** 2 + a * (x1 - 1) ** 2


def calculate_order_of_convergence(
    xk: tuple[float, float],
    xk_next: tuple[float, float],
    x_star: tuple[float, float],
) -> float:
    numerator = np.log(
        np.linalg.norm([[xk_next[0] - x_star[0]], [xk_next[1] - x_star[1]]])
    )
    denominator = np.log(np.linalg.norm([[xk[0] - x_star[0]], [xk[1] - x_star[1]]]))
    result = numerator / denominator
    return result


def calculate_convergence_speed(
    a: float,
    xk: tuple[float, float],
    xk_next: tuple[float, float],
    x_star: tuple[float, float],
) -> float:
    numerator = func(xk_next[0], xk_next[1], a) - func(x_star[0], x_star[1], a)
    denominator = func(xk[0], xk[1], a) - func(x_star[0], x_star[1], a)
    result = numerator / denominator
    return result


def extract_file_content() -> list[list[float]]:
    content = []
    with open("input.txt", mode="r", encoding="utf-8") as file:
        for line in file.readlines():
            current_measurement = [float(value) for value in line.split()]
            content.append(current_measurement)
    return content


def main():
    a = 1
    x_star = [1, 1]

    result_str = "Оценка скорости сходимости\tОценка порядка сходимости\n"

    content = extract_file_content()
    for i in range(len(content) - 1):
        xk = content[i]
        xk_next = content[i + 1]
        convergence_speed = calculate_convergence_speed(a, xk, xk_next, x_star)
        order_of_convergence = calculate_order_of_convergence(xk, xk_next, x_star)
        result_str += f"{convergence_speed}\t{order_of_convergence}\n"

    print(result_str)
    with open("out.txt", mode="w", encoding="utf-8") as output_file:
        print(result_str, file=output_file)


if __name__ == "__main__":
    main()
