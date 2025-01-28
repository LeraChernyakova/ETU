import matplotlib.pyplot as plt
import numpy as np

L = 28
D = 0.8
α_deg = 20
N = 1000

# N = D * 10000 => 29.495711234727075
# N = D * 30000 => 29.494294922351717

def calc_n(y):
    return 1.4 - 0.14 * (y ** 4)

def calc_refraction_angle(sin_incidence_angle, y, dy):
    n1 = calc_n(y)
    n2 = calc_n(y + dy)
    if ((n1 * sin_incidence_angle > n2) or (abs(y + dy) > D)):
        return (sin_incidence_angle, True)
    return (n1 / n2 * sin_incidence_angle, False)

zs = np.array([0])
ys = np.array([0])
sin_cur_angle = np.sin((90 - α_deg) * np.pi / 180)
y = 0
dy = D / N
ans = 0

while L > 0:
    dz = abs(dy) * (sin_cur_angle / np.sqrt(1 - sin_cur_angle ** 2))
    L -= dz
    ans += dz / sin_cur_angle

    zs = np.append(zs, zs[-1] + dz)
    ys = np.append(ys, ys[-1] + dy)

    res_of_incident = calc_refraction_angle(sin_cur_angle, y, dy)
    y += dy


    if (res_of_incident[1]):
        dy = -dy


    sin_cur_angle = res_of_incident[0]

print(ans)
with open("results.txt", "w") as f:
    f.write(ans.__str__())

plt.plot(zs, ys)
plt.xlabel('z')
plt.ylabel('y')
plt.ylim(-D, D)
plt.grid()
plt.savefig("graphic.png")
plt.show()