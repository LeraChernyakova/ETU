import matplotlib.pyplot as plt
import numpy as np
import math
import cmath
from scipy.fft import ifft


L = 65.5e-3
R = 187


def H(w):
    return complex((w * L) ** 2, 0) + complex(0, w * L * R) / complex((w * L) ** 2 + R**2, 0)


def A(w):
    return (w * L) / math.sqrt((w * L) ** 2 + R**2)


def plot_afc(omegas):
    y = []
    for w in omegas:
        y.append(A(w * 2 * math.pi))
    plt.plot(omegas, y)
    plt.grid(True)
    plt.xlabel("Частота w, Hz")
    plt.ylabel(r"$\frac{A_2}{A_1}$")
    plt.show()


def plot_pfc(omegas):
    y = []
    for w in omegas:
        y.append(cmath.phase(H(2 * math.pi * w)))
    plt.plot(omegas, y)
    plt.grid(True)
    plt.xlabel("Частота w, Hz")
    plt.ylabel(r"$arg(H(x))$")
    plt.show()


def plot_green(omegas):
    H_con = []
    for w in omegas:
        H_con.append(H(w * 2 * math.pi).conjugate())
    y = ifft(H_con)
    t = np.arange(20000)
    plt.plot(t[:100].real, y[:100])
    plt.grid(True)
    plt.xlabel("Время t")
    plt.ylabel("Значение функции Грина g(t)")
    plt.show()


omegas = np.linspace(0.0001, 10000, 20000)
plot_afc(omegas)
plot_pfc(omegas)
plot_green(omegas)

