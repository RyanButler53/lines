The problem is as follows: 

Given a list of lines (with unique slopes) determine which line has the highest y value at all x values. 

The executables are built using cmake and run using the shell scripts `./lines` and `./trails`. `./lines` has no arguments and solves the problem with 20 randomly (ish) generated lines and plots the solution. I've found that more than 20 lines is not typically very interesting. 
`./trails` solves n problems and visualizes them on top of each other. There is the option to choose how many solutions to layer on. The color scheme can also be changed. 

There is a mostly full suite of tests for the Lines, Point, Fraction and Toplines classes however extensive fuzz testing occasionally reveals a crash. 
