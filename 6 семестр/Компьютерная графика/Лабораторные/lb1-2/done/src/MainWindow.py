from OpenGL.GL import *
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QMainWindow, QWidget, QHBoxLayout, QVBoxLayout, QLabel, QSlider, QComboBox

from GLScene import GLScene


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        #Инициализация переменных
        self.pickers = {}
        self.all_QComboBox = {}
        self.slider_labels = {}
        self.init_pickers()
        self.init_primitives()
        self.init_alpha()
        self.init_sfactor()
        self.init_dfactor()

        #Инициализация экрана
        self.init_layout()

    def init_layout(self):
        self.setGeometry(100, 100, 800, 600)
        self.central_widget = QWidget()
        self.layout = QHBoxLayout()
        self.vertical_layout = QVBoxLayout()
        self.layout.addLayout(self.vertical_layout)
        self.central_widget.setLayout(self.layout)
        self.setCentralWidget(self.central_widget)

        self.gl_widget = GLScene()
        self.layout.addWidget(self.gl_widget)

        self.create_text("Лабораторная работа №1", self.vertical_layout)
        self.create_text("Примитивы OpenGL", self.vertical_layout)
        self.vertical_layout.addWidget(self.pickers['primitives'])

        self.create_text("Лабораторная работа №2", self.vertical_layout)
        self.create_text("Тест прозрачности", self.vertical_layout)

        self.vertical_layout.addWidget(self.pickers['alpha'])

        self.create_slider(0, 100, 100, 'a', self.vertical_layout)

        self.create_text("Тест смешения цветов", self.vertical_layout)

        self.create_text("sfactor", self.vertical_layout)

        self.vertical_layout.addWidget(self.pickers['sfactor'])

        self.create_text("dfactor", self.vertical_layout)

        self.vertical_layout.addWidget(self.pickers['dfactor'])

        self.create_text("Тест отсечения", self.vertical_layout)

        self.create_text("x", self.vertical_layout)
        self.create_slider(0, 800, 0, 'x', self.vertical_layout)
        self.create_text("y", self.vertical_layout)
        self.create_slider(0, 600, 0, 'y', self.vertical_layout)
        self.create_text("Ширина", self.vertical_layout)
        self.create_slider(0, 600, 600, 'w', self.vertical_layout)
        self.create_text("Высота", self.vertical_layout)
        self.create_slider(0, 800, 800, 'h', self.vertical_layout)


    def init_primitives(self):
        self.primitives = {"GL_POINTS": GL_POINTS,
                           "GL_LINES": GL_LINES,
                           "GL_LINE_STRIP": GL_LINE_STRIP,
                           "GL_LINE_LOOP": GL_LINE_LOOP,
                           "GL_TRIANGLES": GL_TRIANGLES,
                           "GL_TRIANGLE_STRIP": GL_TRIANGLE_STRIP,
                           "GL_TRIANGLE_FAN": GL_TRIANGLE_FAN,
                           "GL_QUADS": GL_QUADS,
                           "GL_QUAD_STRIP": GL_QUAD_STRIP,
                           "GL_POLYGON": GL_POLYGON
                           }
        self.all_QComboBox['primitives'] = self.primitives
        self.init_QComboBox('primitives')


    def init_alpha(self):
        self.alpha = {"GL_ALWAYS": GL_ALWAYS,
                      "GL_NEVER": GL_NEVER,
                      "GL_LESS": GL_LESS,
                      "GL_EQUAL": GL_EQUAL,
                      "GL_LEQUAL": GL_LEQUAL,
                      "GL_GREATER": GL_GREATER,
                      "GL_NOTEQUAL": GL_NOTEQUAL,
                      "GL_GEQUAL": GL_GEQUAL
                      }
        self.all_QComboBox['alpha'] = self.alpha
        self.init_QComboBox('alpha')

    def init_sfactor(self):
        self.sfactor = {"GL_ONE": GL_ONE,
                        "GL_ZERO": GL_ZERO,
                        "GL_DST_COLOR": GL_DST_COLOR,
                        "GL_ONE_MINUS_DST_COLOR": GL_ONE_MINUS_DST_COLOR,
                        "GL_SRC_ALPHA": GL_SRC_ALPHA,
                        "GL_ONE_MINUS_SRC_ALPHA": GL_ONE_MINUS_SRC_ALPHA,
                        "GL_DST_ALPHA": GL_DST_ALPHA,
                        "GL_ONE_MINUS_DST_ALPHA": GL_ONE_MINUS_DST_ALPHA,
                        "GL_SRC_ALPHA_SATURATE": GL_SRC_ALPHA_SATURATE
                        }
        self.all_QComboBox['sfactor'] = self.sfactor
        self.init_QComboBox('sfactor')

    def init_dfactor(self):
        self.dfactor = {"GL_ONE": GL_ONE,
                        "GL_ZERO": GL_ZERO,
                        "GL_SRC_COLOR": GL_SRC_COLOR,
                        "GL_ONE_MINUS_SRC_COLOR": GL_ONE_MINUS_SRC_COLOR,
                        "GL_SRC_ALPHA": GL_SRC_ALPHA,
                        "GL_ONE_MINUS_SRC_ALPHA": GL_ONE_MINUS_SRC_ALPHA,
                        "GL_DST_ALPHA": GL_DST_ALPHA,
                        "GL_ONE_MINUS_DST_ALPHA": GL_ONE_MINUS_DST_ALPHA
                        }
        self.all_QComboBox['dfactor'] = self.dfactor
        self.init_QComboBox('dfactor')

    def init_pickers(self):
        self.pickers['primitives'] = QComboBox()
        self.pickers['alpha'] = QComboBox()
        self.pickers['sfactor'] = QComboBox()
        self.pickers['dfactor'] = QComboBox()

    def init_QComboBox(self, box_type):
        self.pickers[box_type].addItems(self.all_QComboBox[box_type].keys())
        self.pickers[box_type].setCurrentText(next(iter(self.all_QComboBox[box_type].keys())))
        self.pickers[box_type].currentTextChanged.connect(self.on_picker_current_text_changed)


    def on_picker_current_text_changed(self, text):
        if text in self.primitives:
            self.gl_widget.primitiveMode = self.all_QComboBox['primitives'][text]
        elif text in self.alpha:
            self.gl_widget.alpha = self.all_QComboBox['alpha'][text]
        elif text in self.sfactor:
            self.gl_widget.sfactor = self.all_QComboBox['sfactor'][text]
        elif text in self.dfactor:
            self.gl_widget.dfactor = self.all_QComboBox['dfactor'][text]
        self.gl_widget.update()

    def create_slider(self, min_value, max_value, start_value, slider_name, layout):
        slider = QSlider(Qt.Horizontal)
        slider.setFixedWidth(200)
        slider.setMinimum(min_value)
        slider.setMaximum(max_value)
        slider.setValue(start_value)
        slider.setTickInterval(10)
        slider.setTickPosition(QSlider.TicksBelow)
        slider.setObjectName(slider_name)
        slider.valueChanged.connect(self.on_slider_value_changed)
        layout.addWidget(slider)

        if slider_name == 'a':
            self.slider_labels[slider_name] = QLabel(f"Выбранное значение: {start_value / 100}", self)
        else:
            self.slider_labels[slider_name] = QLabel(f"Выбранное значение: {start_value}", self)
        layout.addWidget(self.slider_labels[slider_name])

    def on_slider_value_changed(self, value):
        sender = self.sender()
        slider_name = sender.objectName()

        if slider_name == 'x':
            self.slider_labels['x'].setText(f"Выбранное значение: {value}")
            self.gl_widget.x = value
        elif slider_name == 'y':
            self.slider_labels['y'].setText(f"Выбранное значение: {value}")
            self.gl_widget.y = value
        elif slider_name == 'w':
            self.slider_labels['w'].setText(f"Выбранное значение: {value}")
            self.gl_widget.width = value
        elif slider_name == 'h':
            self.slider_labels['h'].setText(f"Выбранное значение: {value}")
            self.gl_widget.height = value
        elif slider_name == 'a':
            self.slider_labels['a'].setText(f"Выбранное значение: {value / 100}")
            self.gl_widget.alpha_value = value / 100
        self.gl_widget.update()


    def create_text(self, text, layout):
        title = QLabel(text)
        title.setMaximumHeight(15)
        layout.addWidget(title)