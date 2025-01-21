import numpy as np
from OpenGL.GL import *
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QOpenGLWidget
from CountNURBS import buildNurbs


class GLScene(QOpenGLWidget):
    def __init__(self, parent=None):
        super(GLScene, self).__init__(parent)
        self.frameHeight = None
        self.frameWidth = None
        self.x = 0
        self.y = 0
        self.width = 600
        self.height = 800
        self.selected_point = None

        # Контрольные точки
        self.P = [
            np.array([-0.9, -0.9]),
            np.array([-0.700, -0.3]),
            np.array([0.5, -0.4]),
            np.array([-0.200, -0.7]),
            np.array([0.9, 0.9])
        ]

        # Узловой вектор
        self.T = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

        # Веса контрольных точек
        self.W = [1, 10, 100, 46, 1]

        # Базисные функции
        self.f, N = buildNurbs(self.T, self.P, self.W)

    def initializeGL(self):
        glClearColor(1.0, 1.0, 1.0, 0.0)
        glPointSize(7.0)
        glLineWidth(1.5)

    def resizeGL(self, width, height):
        self.frameWidth = width
        self.frameHeight = height

        glViewport(0, 0, width, height)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        aspect_ratio = width / height
        if width <= height:
            glOrtho(-1.0, 1.0, -1.0 / aspect_ratio, 1.0 / aspect_ratio, -1.0, 1.0)
        else:
            glOrtho(-1.0 * aspect_ratio, 1.0 * aspect_ratio, -1.0, 1.0, -1.0, 1.0)
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()

    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        # Построение контрольных точек
        glBegin(GL_POINTS)
        for i, point in enumerate(self.P):
            if i == self.selected_point:
                glColor3dv((0, 1, 0))
            else:
                glColor3dv((1, 0, 0))
            glVertex2dv(point)
        glEnd()

        # Построение основных линий через контрольные точки
        glBegin(GL_LINE_STRIP)
        glColor3dv((0, 0, 1))
        for points in self.P:
            glVertex2dv(points)
        glEnd()

        # Построение NURBS-слпайна
        glBegin(GL_LINE_STRIP)
        glColor3dv((0, 0, 0))
        x = np.linspace(1, 8, 1000)
        points_ = [self.F(x_) for x_ in x]
        for p in points_:
            glVertex2dv(p)
        glEnd()

    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            x = (event.x() / self.width) * 2 - 1
            y = ((self.height - event.y()) / self.height) * 2 - 1
            min_distance = float('inf')
            self.selected_point = None
            for i, point in enumerate(self.P):
                distance = np.linalg.norm(point - np.array([x, y]))
                if distance < min_distance:
                    min_distance = distance
                    self.selected_point = i
            self.update()

    def mouseMoveEvent(self, event):
        if event.buttons() == Qt.LeftButton and self.selected_point is not None:
            pos = event.pos()
            x_point = pos.x() / self.width * 2 - 1
            y_point = 1 - pos.y() / self.height * 2
            self.P[self.selected_point] = np.array([x_point, y_point])
            self.update()

    def mouseReleaseEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.selected_point = None
            self.update()
