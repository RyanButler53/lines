#include <iostream>
#include "lines.hpp"

// Production code
using namespace std; 

int main(int argc, char** argv){
    int numTrails = 4;
    bool separate = true;
    if (argc > 1) {
        numTrails = stoi(argv[1]);
    }
    if (argc > 2) {
        separate = (stoi(argv[2]) == 0);
    }

    std::vector<Line> lines = linesFromFile("");

    // Split lines into numTrails:
    cout << numTrails << endl;
    vector<vector<Line>> linesVector(numTrails);
    if (separate){ // Separate Trails
        for (size_t i = 0; i < lines.size(); ++i) {
            linesVector[i % numTrails].push_back(lines[i]);
        }
    } else { // Compounding Trails
        for (size_t i = 0; i < numTrails-1; ++i){
            size_t bound = (lines.size() / numTrails) * (i + 1);
            for (size_t j = 0; j < bound;++j){
                linesVector[i].push_back(lines[j]);
            }
        }
    linesVector.back() = lines;
    }

    // Print All solutions
    for (auto &lv : linesVector)
    {
        TopLines solution = intersecting_lines(lv);
        cout << solution << endl;
    }

    //Print all the lines
    for (auto& l : lines){ 
        cout << l << "\n";
    }
    return 0;
}