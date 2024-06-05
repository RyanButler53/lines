from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QApplication,
    QLineEdit,
    QMainWindow,
    QLabel,
    QPushButton,
    QTabWidget,
    QComboBox,
    QVBoxLayout,
    QHBoxLayout,
    QGridLayout,
    QWidget,
)


COLOR_MAPS = ['random', 'viridis', 'plasma', 'inferno', 'magma', 'cividis','spring', 
              'summer', 'autumn', 'winter', 'cool', 'Wistia']

app = QApplication([])

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Intersecting Lines Visualizer")
        self.setFixedWidth(500)

        self.initialize_left()
        self.initialize_right()
        
        left = QWidget()
        left.setLayout(self.leftLayout)

        right = QWidget()
        right.setLayout(self.rightLayout)

        tabs = QTabWidget()
        tabs.setTabPosition(QTabWidget.TabPosition.North)
        tabs.setMovable(False)
        tabs.addTab(left,"Visualize Solution")
        tabs.addTab(right, "Random Artwork")

        # Set the central widget of the Window.
        self.setCentralWidget(tabs)

    def initialize_left(self):        
        # Initialize Overall Layout
        self.leftLayout = QVBoxLayout()
        
        # Make Title
        title = self.make_title("Manually Input Lines (Max: 25)")
        self.leftLayout.addWidget(title)
        
        # Set up buttons
        addLine = QPushButton("Add Line")
        visualize = QPushButton("Visualize")
        clear = QPushButton("Clear")
        addLine.clicked.connect(self.add_line_box)
        visualize.clicked.connect(self.visualize)

        buttons = QHBoxLayout()
        buttons.addWidget(addLine)
        buttons.addWidget(visualize)
        self.leftLayout.addLayout(buttons)

        # Will store all the left sublayouts for lines
        self.lineBoxes = []

        # Left Sublayout. Has a label then a text edit box
        for _ in range(5):
            self.add_line_box()
        firstLine = self.lineBoxes[0].itemAt(1).widget()
        firstLine.setPlaceholderText("y = 2x + 3")


    def add_line_box(self):
        numLines = len(self.lineBoxes)
        if (numLines > 24):
            return
        leftLayout = QHBoxLayout()
        leftLayout.addWidget(QLabel(f"Line {numLines+1}:"))
        leftLayout.addWidget(QLineEdit())
        self.lineBoxes.append(leftLayout)
        self.leftLayout.addLayout(leftLayout)

    def make_title(self,text):
        title = QLabel(text)
        font = title.font()
        font.setPointSize(20)
        title.setFont(font)
        title.setAlignment(Qt.AlignmentFlag.AlignHCenter | Qt.AlignmentFlag.AlignTop)
        return title
    
    def visualize(self):
        pass

    def clear(self):
        pass


    def initialize_right(self):

        self.rightLayout = QVBoxLayout()
        title = self.make_title("Randomly Generated Trails of Top Lines")
        self.rightLayout.addWidget(title)

        # Grid
        rightGrid = QGridLayout()
        
        #Number of lines
        rightGrid.addWidget(QLabel("Number of\nRandom Lines"),0,0)
        field = QLineEdit()
        field.setInputMask('0000')
        field.setPlaceholderText("20")
        rightGrid.addWidget(field,0,1)

        #color Scheme
        rightGrid.addWidget(QLabel("Matplotlib\nColor Scheme"),1,0)
        dropdown = QComboBox()
        dropdown.addItems(COLOR_MAPS)
        rightGrid.addWidget(dropdown,1,1)
        # Add default to random

        # Number of Trails
        rightGrid.addWidget(QLabel("Number of\nTrails"),2,0)
        field = QLineEdit()
        field.setInputMask('0000')
        field.setPlaceholderText("4")
        rightGrid.addWidget(field,2,1)
        #default to 4

        # Output filename
        rightGrid.addWidget(QLabel("Output Filename"),3,0)
        output = QLineEdit()
        output.setPlaceholderText("image.png")
        rightGrid.addWidget(output,3,1)

        self.rightLayout.addLayout(rightGrid)

        generateButton = QPushButton("Generate Art")
        generateButton.clicked.connect(self.generateArt)

        self.rightLayout.addWidget(generateButton)

    def generateArt(self):
        print("generating art")

# Create a Qt widget, which will be our window.
window = MainWindow()
window.show()  

app.exec()
