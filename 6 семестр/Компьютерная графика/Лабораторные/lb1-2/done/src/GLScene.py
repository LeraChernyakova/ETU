import math
import random

from OpenGL.GL import *
from PyQt5.QtOpenGL import QGLWidget



class GLScene(QGLWidget):
    def __init__(self, parent=None):
        super(GLScene, self).__init__(parent)
        self.primitiveMode = GL_POINTS
        self.alpha = GL_ALWAYS
        self.alpha_value = 1.0
        self.sfactor = GL_ONE
        self.dfactor = GL_ONE
        self.x = 0
        self.y = 0
        self.width = 600
        self.height = 800

    def initializeGL(self):
        glClearColor(0.0, 0.0, 0.0, 1.0)
        glPointSize(5.0)
        glLineWidth(3.0)

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

        colors = [
            (0.0, 1.0, 1.0, 0.42), (1.0, 0.0, 1.0, 0.66), (0.0, 0.5, 0.0, 0.34),
            (0.5, 0.0, 0.0, 0.92), (0.0, 0.5, 0.5, 0.2), (0.5, 0.0, 0.5, 0.12),
            (0.0, 1.0, 0.0, 0.55), (1.0, 0.0, 0.0, 0.81), (1.0, 1.0, 0.0, 0.72),
            (0.0, 0.0, 1.0, 0.32)
        ]

        num_points = 12
        radius = 0.7

        glEnable(GL_ALPHA_TEST)
        glEnable(GL_BLEND)
        glEnable(GL_SCISSOR_TEST)
        glAlphaFunc(self.alpha, self.alpha_value)
        glBlendFunc(self.sfactor, self.dfactor)
        glScissor(self.x, self.y, self.width, self.height)


        glBegin(self.primitiveMode)
        for point in range(num_points):
            glColor4f(colors[point % len(colors)][0], colors[point % len(colors)][1], colors[point % len(colors)][2],
                      colors[point % len(colors)][3])
            angle = 2 * math.pi * point / num_points
            x = radius * math.cos(angle)
            y = radius * math.sin(angle)
            glVertex2f(x, y)
        glEnd()

        glDisable(GL_SCISSOR_TEST)
        glDisable(GL_ALPHA_TEST)
        glDisable(GL_BLEND)

