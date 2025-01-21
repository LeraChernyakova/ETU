from PyQt5.QtCore import pyqtSlot
from PyQt5.QtWidgets import QMainWindow, QSplitter, QWidget, QHBoxLayout, QLabel, QSpinBox
from GLScene import GLScene


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.gl_widget = GLScene()
        self.iterations = QSpinBox()
        self.iterations.setRange(0, 8)

        layout = QHBoxLayout()
        label = QLabel("Количество итераций")
        layout.addWidget(label)
        layout.addWidget(self.iterations)
        layout.setContentsMargins(0, 0, 0, 0)

        sp = QSplitter()
        sp.addWidget(self.gl_widget)
        widget = QWidget()
        widget.setLayout(layout)
        sp.addWidget(widget)
        sp.setStretchFactor(0, 1)

        self.setCentralWidget(sp)
        self.connectSignals()
        self.setFixedSize(800, 800)

    @pyqtSlot(int)
    def iterationChanged(self, value):
        self.gl_widget.iterations = value
        self.gl_widget.update()
        pass

    def connectSignals(self):
        self.iterations.valueChanged.connect(self.iterationChanged)
