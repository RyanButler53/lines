#include <iostream>
// #include "lines.cpp"
#include "lines.hpp"

// Production code
using namespace std; 

int main(int argc, char** argv){
    string filename = "20lines.txt"; //"inputs/9lines.txt";
    if (argc >1)
    {
        filename = argv[1];
    }
    std::vector<Line> lines = linesFromFile(filename);
    TopLines soln = intersecting_lines(lines);
    cout << soln << endl;
    cout << filename << endl; // get all lines
    return 0;
}
