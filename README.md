The problem is as follows: 

Given a list of lines (with unique slopes) determine which line has the highest y value at all x values. 

Software Requirements: 
- Python: Pyqt6, matplotlib, numpy, pytest. 
- C++: C++ compiler with C++20 support
- Build: Cmake with CTest

### Running
Recommend running in a python virtual environment.

Build Python Bindings: `pip install .`

Run: `lines`

### Testing 
Build Tests: `cmake -S . -B build && cmake --build build --parallel 5` 

Run Tests: 
- C++ Tests: `cd build && ctest .`
- Python Tests (Requires pytest) `pytest tests`


In the GUI, there are two tabs. One will visualize the top lines and the other will attempt to create some random art. For the visualization, input the lines in y=mx+b (omitting the y=) form. Maximum of 25 lines. The visualization will be output in "figure1.png"
For the random artwork, there is a maximum of 50 lines and no more than half of the number of lines can be highlighted

Todos:
- Make the tests more robust by copying input files into build folder and setting the path as a #define
- Use a parameterized test to clean up code duplication in the tests
