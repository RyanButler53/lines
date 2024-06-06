The problem is as follows: 

Given a list of lines (with unique slopes) determine which line has the highest y value at all x values. 

Software Requirements: Must have gcc, cmake, python3 and pyqt6. 

Build: `cmake --build build`

Run: `./run` or `python3 src/main.py`. 

In the GUI, there are two tabs. One will visualize the top lines and the other will attempt to create some random art. For the visualization, input the lines in y=mx+b (omitting the y=) form. Maximum of 25 lines
For the random artwork, there is a maximum of 50 lines and no more than half of the number of lines can be highlighted (this is an odd issue, will look into)

There is a mostly full suite of tests for the Lines, Point, Fraction and Toplines classes however extensive fuzz testing occasionally reveals a crash. 
