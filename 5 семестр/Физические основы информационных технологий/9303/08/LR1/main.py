import math
import matplotlib.pyplot as plt


def n(y):
    return 1.3 - 0.12 * math.cos(math.radians(3 * y))


z = [0]
y = [0]
length = 0
N = 1000
D = 0.8
L = 18
beta = 20
n2 = 1
curY = 0
curZ = 0
deltaY = D / N
n0 = n(0)
while curZ < L:
    deltaZ = abs(deltaY) / math.tan(math.radians(beta))
    alpha0 = 90 - beta
    n1 = n(curY + deltaY)
    alpha1 = math.degrees(math.asin(n0 / n1 * math.sin(math.radians(alpha0))))
    beta = 90 - alpha1
    n0 = n1
    curY += deltaY
    curZ += deltaZ
    z.append(curZ)
    y.append(curY)
    length += math.sqrt(deltaZ**2 + deltaY**2)
    if abs(curY) >= D:
        deltaY = -deltaY
        beta = 90 - alpha0

res = open("results.txt", "w")
res.write(str(length))
res.close()
plt.plot(z, y, "r")
plt.grid()
plt.show()
