from OpenGL import GL as gl
import numpy as np

# Нормализованные векторы точек шестиугольника
hexagon = np.array([
    np.array([np.cos(t), np.sin(t)])
    for t in np.linspace(0, 2 * np.pi, 7)[:-1] + np.pi / 6
])


# Генерация n уровней вложенных шестиугольников на расстоянии r
def generate(n, r):
    return [i * r * hexagon for i in range(n)]


# Палитра цветов
colors = [
    [0.06, 0.28, 0.66],
    [0.78, 0.0, 0.49],
    [0.66, 0.94, 0.0],
    [1.0, 0.65, 0.0]
]

# Векторы точек окружности
circleVecs = [np.array([np.cos(t), np.sin(t)]) for t in np.linspace(0, 2 * np.pi, 50)]


# Рисование окружности радиуса r в точке p
def drawCircle(r, p, color):
    gl.glBegin(gl.GL_LINE_STRIP)
    gl.glColor3dv(color)
    for a in circleVecs:
        gl.glVertex2dv(p + a * r)
    gl.glEnd()


# Рисованиее линий списка уровней шестиугольников
def drawLines(dots):
    gl.glBegin(gl.GL_LINES)
    # Уровни
    for i in range(1, len(dots)):
        # Точки в уровне
        for j in range(6):
            gl.glColor3dv(colors[j % 4])
            # Соединение точки с двумя другими на своём уровне
            for k in range(1, 3):
                gl.glVertex2dv(dots[i][j])
                gl.glVertex2dv(dots[i][j - 2 * k])
            # Соединение точки с двумя точками предыдущего уровня
            gl.glVertex2dv(dots[i][j])
            gl.glVertex2dv(dots[i - 1][j - 1])
            gl.glVertex2dv(dots[i][j])
            gl.glVertex2dv(dots[i - 1][(j + 1) % 6])
    gl.glEnd()
