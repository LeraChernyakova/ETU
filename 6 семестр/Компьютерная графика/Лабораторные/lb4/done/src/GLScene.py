from OpenGL.GL import *
from OpenGL.raw.GLU import gluOrtho2D, gluPerspective
from PyQt5.QtWidgets import QOpenGLWidget
from Rectangle import createRectangle
from Rectangle import paintRectangle
from FractalGenerator import fractalGenerator

ZERO_LEVEL = 200


class GLScene(QOpenGLWidget):
    def __init__(self, parent=None):
        super(GLScene, self).__init__(parent)
        self.frameHeight = None
        self.frameWidth = None
        self.width = 640
        self.height = 640

        self.angle = 0
        self.iterations = 0
        self.old_rectangles = [
            createRectangle(self.width / 2, self.height / 2, self.angle, ZERO_LEVEL, ZERO_LEVEL)
        ]
        self.new_rectangles = []
        self.steps = {0: self.old_rectangles}

    def initializeGL(self):
        glClearColor(1.0, 1.0, 1.0, 0.0)

    def resizeGL(self, width, height):
        self.frameWidth = width
        self.frameHeight = height
        glViewport(0, 0, width, height)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluOrtho2D(0, width, 0, height)
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()

    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        fractalGenerator(self)
        for rectangle in self.old_rectangles:
            paintRectangle(rectangle)
