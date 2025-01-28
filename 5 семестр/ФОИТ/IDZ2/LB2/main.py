import matplotlib.pyplot as plt
import numpy as np
import scipy.special
import scipy.optimize
from scipy.interpolate import interp1d
from scipy.constants import speed_of_light

R = 1
e = 5.4
f0 = 13
t_1 = 1 / f0 * 10
t_2 = 1 / f0 * 30
t_3 = 1 / f0
P = 0.4
c = speed_of_light


def Heaviside(x):  # Ступенчатая функция
    return 0 if x < 0 else 1


def signal(t):  # Описание сигнала
    return np.sin(f0 * 2 * np.pi * t) * (Heaviside(t - t_1) - Heaviside(t))


def Signal(t, z, N1=60):
    sum = 0
    for k in range(0, N1 + 1):
        if f_gr < f_k[k] < fl_k[99]:
            sum += spectrum2[k] * np.cos(
                f_k[k] * 2 * np.pi * t - f_k[k] * 2 * np.pi / (v_f(f_k[k]) * c / (10 ** 9)) * z)
    return sum


def Vfc_plot(v_f, v_fk, xnew, fl_k):
    fig, ax = plt.subplots()
    ax.plot(fl_k, v_fk[1:], 'o', xnew, v_f(xnew), '-')
    ax.set_xlabel('f')
    ax.set_ylabel('V_f')
    ax.grid(True)
    plt.show()


def impulse_plot():
    N = 2 ** 10
    time = [t_2 * i / (N - 1) for i in range(0, N)]  # Моменты времени для построения графика
    point_s = [signal(i) for i in time]
    fig, ax = plt.subplots()
    ax.plot(time, point_s)
    ax.set_xlabel('t')
    ax.grid(True)
    plt.show()


def Inverse_Fourier_transform_plot(time, sigout):
    fig, ax = plt.subplots()
    ax.plot(time, sigout, 'r')
    ax.set_xlabel('time')
    ax.set_ylabel('SigOut')
    ax.grid(True)
    plt.show()


"""1. Построение графика зависимости фазовой скорости от частоты. Опредление пороговой частоты"""


def first_task():
    def dispersion_equation(v_fc):  # Дисперсионное уравнение
        return scipy.special.j0(R * frequencies[i] / c * np.sqrt(e - 1 / v_fc ** 2))

    frequencies = [2 * np.pi * (5 + 20 * i / 100) * 10 ** 9 for i in range(101)]  # Частоты для поиска фазовых скоростей
    v_fc = 2  # Начальное приближение
    i = 0
    res = scipy.optimize.root(dispersion_equation, v_fc)  # Поиск первой фазовой скорости
    v_f0 = res.x[0]

    v_fk = [v_f0]  # Фазовые скорости
    fl_k = []  # Частоты f

    # Поиск последующих фазовых скоростей
    for k in range(1, 101):
        i += 1
        v_fc = v_fk[k - 1]
        res = scipy.optimize.root(dispersion_equation, v_fc, method='lm')
        v_fk.append(res.x[0])
        fl_k.append(frequencies[i] / (2 * np.pi * 10 ** 9))

    f_gr = fl_k[1]  # Граничная частота

    """ Апроксимация массива фазовых скоростей """
    v_f = interp1d(fl_k, v_fk[1:])  # Функция фазовой скорости от частоты
    xnew = np.linspace(fl_k[0], fl_k[-1], num=500, endpoint=True)
    Vfc_plot(v_f, v_fk, xnew, fl_k)

    """ Построение графика импульса """
    impulse_plot()
    return f_gr, fl_k, v_f


"""2. Построение спектра сигнала """


def second_task(f_gr):
    def sin_x(x):
        return 1 if x == 0 else np.sin(x) / x

    def spectrum(f):  # Определение функции спектра радиоимпульса
        return sin_x((f - f0) * 2 * np.pi * t_1 / 2) * t_1

    N1 = 60
    f_k = [k / t_2 for k in range(0, N1 + 1)]  # Частоты, задающие интервалы между импульсами

    spectrum1 = [np.abs(spectrum(f)) for f in f_k]
    spectrum2 = [spectrum(f) for f in f_k]
    point_spec = [s / max(spectrum1) for s in spectrum1]

    # График спектра
    fig, ax = plt.subplots()
    ax.plot(f_k, point_spec, 'o-')
    ax.vlines(f_gr, 0, 1, colors='r', linestyles='dashed', label="f_gr")
    for k in range(0, len(f_k)):
        ax.vlines(f_k[k], 0, point_spec[k], colors="b", linestyles='dashed')

    ax.set_xlabel('f_k')
    ax.set_ylabel('spectrum/max(spectrum)')
    ax.grid(True)
    plt.show()
    return f_k, spectrum2


""" 3. Обратное преобразование Фурье"""


def third_task():
    N = 1000
    z = 0
    time = [4 * t_2 * i / (N - 1) for i in range(0, N)]
    sigout = [Signal(t - t_1 / 2, z) for t in time]
    Inverse_Fourier_transform_plot(time, sigout)


"""4. Построение зависимости последовательности импульсов от расстояния."""


def fourth_task():
    N = 1000
    Number = 0
    dist = [Number + i / N*4 for i in range(0, N + 1)]
    time = [4 * t_2 * i / (N - 1) for i in range(0, N)]
    time1 = 0
    sigout2 = [Signal(time1 + t_1 / 2, d) for d in dist]

    fig, ax = plt.subplots()
    ax.plot(dist, sigout2, 'r')
    ax.set_xlabel('dist')
    ax.set_ylabel('SigOut')
    ax.grid(True)
    plt.show()

    # Анализ областей между сигналами на превышении порога

    time_between_pulse = t_2 - t_1

    eps = 0.0025
    flag = 0
    for z in range(100, 110, 1):
        if flag:
            break
        fig, ax = plt.subplots()
        current_time = z * 0.0845

        sigout = [Signal(t - t_1 / 2, z) for t in time]
        lines = []
        for i in range(0, 8):
            lines.append(current_time % 8.5712)
            ax.vlines(current_time % 8.5712, -1.5, 1.5, colors='b', linestyles='dashed')
            current_time += time_between_pulse if i % 2 else t_1

        ax.hlines(P * max(sigout), 0, 8.5712, colors="g", linestyles='dashed')
        ax.hlines(- (P * max(sigout)), 0, 8.5712, colors="g", linestyles='dashed')

        lines.sort()
        count = 1 if lines[0] > t_1 or lines[0] == 0 else 0

        for k in range(len(time)):
            if lines[count] < time[k] < lines[count + 1]:
                if np.abs(sigout[k]) >= P * max(sigout) \
                        and time[k] - lines[count] > eps \
                        and lines[count + 1] - time[k] > eps:
                    print("distance =", z)
                    flag = 1
                    break
            if time[k] > lines[count + 1]:
                if count >= 5:
                    break
                count += 2

        ax.plot(time, sigout, 'r')
        ax.set_xlabel('time')
        ax.set_ylabel('SigOut')
        ax.grid(True)
        plt.show()


f_gr, fl_k, v_f = first_task()
f_k, spectrum2 = second_task(f_gr)
third_task()
fourth_task()
