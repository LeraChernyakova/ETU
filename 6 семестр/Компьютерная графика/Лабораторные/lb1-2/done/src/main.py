import sys

from PyQt5.QtWidgets import QApplication

from MainWindow import MainWindow


def main():
    app = QApplication([])
    window = MainWindow()
    window.show()
    window.setWindowTitle("Чернякова Валерия, Ярусова Татьяна КГ Лаб. 1-2")
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()