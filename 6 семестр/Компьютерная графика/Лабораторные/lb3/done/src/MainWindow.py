from PyQt5.QtWidgets import QMainWindow, QSplitter
from GLScene import GLScene
from ControlPanel import ControlPanel
from CountNURBS import buildNurbs


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.gl_widget = GLScene()

        self.control = ControlPanel(len(self.gl_widget.W), self)
        for i in range(5):
            self.control.wSliders[i].setValue(self.gl_widget.W[i])
        self.onWeightsChanged()
        self.control.weightsChanged.connect(self.onWeightsChanged)

        sp = QSplitter(self)
        sp.addWidget(self.gl_widget)
        sp.addWidget(self.control)
        sp.setStretchFactor(0, 1)
        self.setCentralWidget(sp)
        self.resize(800, 600)

    def onWeightsChanged(self):
        self.gl_widget.W = [s.value() for s in self.control.wSliders]
        self.gl_widget.F, N = buildNurbs(self.gl_widget.T, self.gl_widget.P, self.gl_widget.W)
        self.gl_widget.update()
