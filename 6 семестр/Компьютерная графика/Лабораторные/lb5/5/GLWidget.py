from OpenGL import GL as gl
from PyQt6 import QtCore
from PyQt6.QtOpenGLWidgets import QOpenGLWidget

import shaders


# Виджет OpenGL
class GLWidget(QOpenGLWidget):
    viewPortResized = QtCore.pyqtSignal((int, int))

    def __init__(self, parent=None):
        super().__init__(parent)
        # Функция вызываемая в цикле отрисовки (при обновлениях)
        self.function = None
        self.shader = None

    def resizeGL(self, w: int, h: int) -> None:
        gl.glViewport(0, 0, w, h)
        self.viewPortResized.emit(w, h)

    # Функция вызываемая перед любым обновлением
    def initializeGL(self):
        # Заливка кадра
        gl.glClearColor(0.1, 0.1, 0.1, 1)
        # Очистка буферов (цвета и глубины)
        gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
        # Создание программы шейдера
        self.shader = shaders.createWaveProgram()
        # Подключение шейдера
        gl.glUseProgram(self.shader)
        # Указатели для uniform параметров
        self.freqLocation = gl.glGetUniformLocation(self.shader, "freq")
        self.amplitudeLocation = gl.glGetUniformLocation(self.shader, "amplitude")

    # Функция вызываемая при обновлении (посредством update или при изменении размеров)
    def paintGL(self):
        # Вызов рендер-функции
        if self.function is not None:
            self.function()

    # Изменить частоту волны в шейдере
    def setFreq(self, freq: float):
        if self.shader is not None:
            gl.glUniform1f(self.freqLocation, freq)

    # Изменить амплитуду в шейдере
    def setAmplitude(self, amplitude: float):
        if self.shader is not None:
            gl.glUniform1f(self.amplitudeLocation, amplitude)
