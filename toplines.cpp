#include <iostream>
#include "lines.cpp"
#include "lines.hpp"

// Production code
using namespace std; 
int main()
{
    Point p = intersect(Line{0.5, 0}, Line{getDouble("2/3"), getDouble("-2/3")});
    cout << p << endl;
    cout << getDouble("-2/3") << endl;
    cout << 2.0 / 3 << endl;
    
}
