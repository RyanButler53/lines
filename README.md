The problem is as follows: 

Given a list of lines (with unique slopes) determine which line has the highest y value at all x values. 

Software Requirements: 
- Python: Pyqt6, matplotlib, numpy, pytest. 
- C++ compiler with C++20 support for structured bindings
- Cmake with CTest

Build Tests: `mkdir build && cd build && cmake .. && make -j5`

Run Tests: 
- C++ Tests: `cd build && ctest .`
- Python Tests (Requires pytest) `pytest tests`

Run: `python3 python/main.py` 

In the GUI, there are two tabs. One will visualize the top lines and the other will attempt to create some random art. For the visualization, input the lines in y=mx+b (omitting the y=) form. Maximum of 25 lines
For the random artwork, there is a maximum of 50 lines and no more than half of the number of lines can be highlighted (this is an odd issue, will look into)
