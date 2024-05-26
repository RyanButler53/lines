#include <iostream>
#include "lines.hpp"

// Production code
using namespace std; 

int main(int argc, char** argv){
    string filename = ""; 
    if (argc >1) {
        filename = argv[1];
    }
    std::vector<Line> lines = linesFromFile(filename);
    TopLines soln = intersecting_lines(lines);
    cout << soln << endl;

    // Print all the lines
    for (auto& l : lines){ 
        cout << l << "\n";
    }
    return 0;
}
