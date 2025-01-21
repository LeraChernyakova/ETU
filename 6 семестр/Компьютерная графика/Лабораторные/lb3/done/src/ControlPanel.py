from PyQt5 import QtCore
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QWidget, QVBoxLayout, QLabel, QSlider


class ControlPanel(QWidget):
    # Контрольная панель весов контрольных точек
    weightsChanged = QtCore.pyqtSignal()

    def __init__(self, weights, parent=None):
        super().__init__(parent)
        layout = QVBoxLayout(self)
        self.setLayout(layout)

        weights_label = QLabel('Веса NURBS-сплайна', self)
        w_labels = [QLabel(f'W{i+1}') for i in range(weights)]
        self.wSliders = [QSlider(Qt.Orientation.Horizontal) for _ in range(weights)]

        for w in [weights_label]:
            layout.addWidget(w)

        for i in range(weights):
            layout.addWidget(w_labels[i])
            layout.addWidget(self.wSliders[i])
            self.wSliders[i].valueChanged.connect(lambda: self.weightsChanged.emit())
            self.wSliders[i].setMaximum(100)
            self.wSliders[i].setMinimum(0)

        layout.addStretch()
