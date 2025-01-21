from OpenGL.GL import *
from numpy.ma import cos, sin


def createRectangle(x, y, angle, h, w):
    return {'x': x, 'y': y, 'h': h, 'w': w, 'angle': angle}


def paintRectangle(rectangle):
    x = rectangle['x']
    y = rectangle['y']
    w = rectangle['w']
    h = rectangle['h']
    angle = rectangle['angle']

    glColor3f(0.0, 0.0, 0.0)
    glBegin(GL_LINE_LOOP)
    glVertex2f(x + w * cos(angle) - h * sin(angle), y + w * sin(angle) + h * cos(angle))
    glVertex2f(x + w * cos(angle) + h * sin(angle), y + w * sin(angle) - h * cos(angle))
    glVertex2f(x - w * cos(angle) + h * sin(angle), y - w * sin(angle) - h * cos(angle))
    glVertex2f(x - w * cos(angle) - h * sin(angle), y - w * sin(angle) + h * cos(angle))
    glEnd()
