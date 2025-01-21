from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QWidget, QVBoxLayout, QSlider, QLabel


# Виджет панели управления
class ControlPanel(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        lt = QVBoxLayout(self)
        self.setLayout(lt)

        drawLabel = QLabel('Рисование фрактала', self)
        levelsLabel = QLabel('Количество итераций', self)
        self.iterations = QSlider(Qt.Orientation.Horizontal, self)
        radiusLabel = QLabel('Расстояние между уровнями (масштаб)', self)
        self.radius = QSlider(Qt.Orientation.Horizontal, self)

        shaderLable = QLabel('Парметры шейдера', self)
        waveLable = QLabel('Частота волны', self)
        self.waves = QSlider(Qt.Orientation.Horizontal, self)
        amplitudeLable = QLabel('Амплитуда', self)
        self.amplitude = QSlider(Qt.Orientation.Horizontal, self)

        #
        for i in [
            drawLabel, levelsLabel, self.iterations, radiusLabel, self.radius,
            shaderLable, waveLable, self.waves, amplitudeLable, self.amplitude
        ]:
            lt.addWidget(i)
        lt.addStretch()
