from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QApplication,
    QLineEdit,
    QMainWindow,
    QLabel,
    QPushButton,
    QTabWidget,
    QVBoxLayout,
    QHBoxLayout,
    QWidget,
)
from PyQt6.QtGui import QPalette, QColor

# from PyQt6.QtCore import QSize, Qt
# Only needed for access to command line arguments

# You need one (and only one) QApplication instance per application.
# Pass in sys.argv to allow command line arguments for your app.
# If you know you won't use command line arguments QApplication([]) works too.
app = QApplication([])

class Color(QWidget):

    def __init__(self, color):
        super(Color, self).__init__()
        self.setAutoFillBackground(True)

        palette = self.palette()
        palette.setColor(QPalette.ColorRole.Window, QColor(color))
        self.setPalette(palette)

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Intersecting Lines Visualizer")

        # Set the central widget of the Window.


        self.addbutton = QPushButton("Add")
        self.addbutton.clicked.connect(self.add_left_sublayout)

        self.leftLayout = QVBoxLayout()
        self.leftLayout.addWidget(QLabel("Manually Input Lines"))
        self.leftLayout.addWidget(self.addbutton)


        # Will store all the left sublayouts
        self.lineBoxes = []

        # Left Sublayout. Has a label then a text edit box
        self.add_left_sublayout()
        
        container = QWidget()
        container.setLayout(self.leftLayout)

        tabs = QTabWidget()
        tabs.setTabPosition(QTabWidget.TabPosition.North)
        tabs.setMovable(False)
        tabs.addTab(container,"left")
        tabs.addTab(Color('red'), "right")

        # Set the central widget of the Window.
        self.setCentralWidget(tabs)


    def add_left_sublayout(self):
        numLines = len(self.lineBoxes)
        leftLayout = QHBoxLayout()
        leftLayout.addWidget(QLabel(f"Line {numLines+1}:"))
        leftLayout.addWidget(QLineEdit())
        self.lineBoxes.append(leftLayout)
        self.leftLayout.addLayout(leftLayout)

# Start the event loop.

# Create a Qt widget, which will be our window.
window = MainWindow()
window.show()  

app.exec()
