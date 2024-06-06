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
    QSlider,
    QGridLayout,
    QWidget,
)
import subprocess


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
        firstLine.setPlaceholderText("2x + 3")


    def add_line_box(self):
        numLines = len(self.lineBoxes)
        if (numLines > 24):
            return
        leftLayout = QHBoxLayout()
        leftLayout.addWidget(QLabel(f"Line {numLines+1}: y="))
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
        lines = []
        for layout in self.lineBoxes:
            box = layout.itemAt(1).widget()
            text = box.text()
            if text != "":
                lines.append(text)
        args = ['scripts/ordinary_lines']
        for l in lines:
            args.append(l)
        subprocess.call(args)


    def clear(self):
        pass


    def initialize_right(self):

        self.rightLayout = QVBoxLayout()
        title = self.make_title("Randomly Generated Trails of Top Lines")
        self.rightLayout.addWidget(title)

        # Store the widgets for easy retrival
        self.rightWidgets = []

        # Grid
        rightGrid = QGridLayout()
        
        #Number of lines
        rightGrid.addWidget(QLabel("Number of\nRandom Lines"),0,0)
        field = QLineEdit()
        field.setInputMask('00')
        field.setPlaceholderText("20")
        rightGrid.addWidget(field,0,1)
        self.rightWidgets.append(field)

        #color Scheme
        rightGrid.addWidget(QLabel("Matplotlib\nColor Scheme"),1,0)
        color_dropdown = QComboBox()
        color_dropdown.addItems(COLOR_MAPS)
        rightGrid.addWidget(color_dropdown,1,1)
        self.rightWidgets.append(color_dropdown)

        # Number of Trails
        rightGrid.addWidget(QLabel("Number of\nTrails"),2,0)
        field = QLineEdit()
        field.setInputMask('00')
        field.setPlaceholderText("4")
        rightGrid.addWidget(field,2,1)
        self.rightWidgets.append(field)

        rightGrid.addWidget(QLabel("Randomness Level"),3,0)
        slider = QSlider(Qt.Orientation.Horizontal)
        slider.setRange(0,7)
        slider.setSingleStep(1)
        rightGrid.addWidget(slider,3,1)
        self.rightWidgets.append(slider)


        # Output filename
        rightGrid.addWidget(QLabel("Output Filename"),4,0)
        output = QLineEdit()
        output.setPlaceholderText("image.png")
        rightGrid.addWidget(output,4,1)
        self.rightWidgets.append(output)

        self.rightLayout.addLayout(rightGrid)

        generateButton = QPushButton("Generate Art")
        generateButton.clicked.connect(self.generateArt)

        self.rightLayout.addWidget(generateButton)

    def generateArt(self):
        # Need to get number of lines, max 50
        numLines = self.getNumLines()
        color = self.rightWidgets[1].currentText()
        numTrails = self.getNumTrails(numLines)
        
        jitter = self.rightWidgets[3].value()
        filename = self.rightWidgets[4].text().rstrip(".png")
        if filename == "":
            filename = "images/trails"
        args = [str(arg) for arg in [numLines, color, numTrails, jitter, filename+".png"]]
        subprocess.call(["scripts/trails"] + args)

    def getNumLines(self):
        try:
            numLines = int(self.rightWidgets[0].text())
        except ValueError as error:
            print("Defaulting to 20 lines")
            return 20
        if numLines > 50:
            print(f"Max Lines is 50")
            return 50
        elif numLines < 2:
            print(f"Min lines is 2")
            return 2
        return numLines
        
    def getNumTrails(self, numLines):
        try: 
            numTrails = int(self.rightWidgets[2].text())
        except ValueError as error:
            numTrails = numLines // 2
        if numTrails > numLines//2:
            print(f"No more than number of lines/2 trails")
            numTrails = numLines//2
        return numTrails

# Create a Qt widget, which will be our window.
window = MainWindow()
window.show()  

app.exec()
